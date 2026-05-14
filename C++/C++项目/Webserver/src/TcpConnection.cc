/**
 * TcpConnection：TCP连接封装类
 * 
 * 设计目的：
 * - 封装单个TCP连接的生命周期
 * - 管理连接状态（连接中、已断开等）
 * - 处理读写事件和连接关闭
 * - 提供用户回调接口
 * 
 * 特点：
 * - 使用shared_ptr管理生命周期
 * - 支持半关闭状态
 * - 提供丰富的回调接口
 */

#include <functional>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/tcp.h>
#include <sys/sendfile.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#include <TcpConnection.h>
#include <Logger.h>
#include <Socket.h>
#include <Channel.h>
#include <EventLoop.h>

static EventLoop *CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL<<" mainLoop is null!";
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop *loop,
                             const std::string &nameArg,
                             int sockfd,
                             const InetAddress &localAddr,
                             const InetAddress &peerAddr)
    : loop_(CheckLoopNotNull(loop))
    , name_(nameArg)
    , state_(kConnecting)
    , reading_(true)
    , socket_(new Socket(sockfd))
    , channel_(new Channel(loop, sockfd))
    , localAddr_(localAddr)
    , peerAddr_(peerAddr)
    , highWaterMark_(64 * 1024 * 1024) // 64M
{
    // 下面给channel设置相应的回调函数 poller给channel通知感兴趣的事件发生了 channel会回调相应的回调函数
    channel_->setReadCallback(
        std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(
        std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(
        std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(
        std::bind(&TcpConnection::handleError, this));

    LOG_INFO<<"TcpConnection::ctor:["<<name_.c_str()<<"]at fd="<<sockfd;
    socket_->setKeepAlive(true);
}

/**
 * TcpConnection析构函数
 * 
 * 确保连接已断开，进行资源清理
 * 
 * 安全检查：
 * - 连接必须处于断开状态
 * - 记录析构日志，便于调试
 */
TcpConnection::~TcpConnection()
{
    LOG_INFO<<"TcpConnection::dtor["<<name_.c_str()<<"]at fd="<<channel_->fd()<<"state="<<(int)state_;
}

/**
 * 发送数据
 * 
 * 线程安全的发送接口：
 * - 如果在IO线程中，直接发送
 * - 如果在其他线程中，投递到IO线程
 * 
 * 流量控制：
 * - 如果应用写入速度快于内核发送速度，数据会暂存在outputBuffer_
 * - 支持设置高水位回调，防止内存无限增长
 * 
 * @param buf: 要发送的数据
 */
void TcpConnection::send(const std::string &buf)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread()) // 在IO线程中，直接发送
        {
            sendInLoop(buf.c_str(), buf.size());
        }
        else // 在其他线程中，需要投递到IO线程
        {
            void (TcpConnection::*fp)(const void *, size_t) = &TcpConnection::sendInLoop;
            loop_->runInLoop(std::bind(fp,
                                        shared_from_this(),  // 使用shared_ptr管理生命周期
                                        buf.c_str(),
                                        buf.size()));
        }
    }
}

/**
 * 发送数据 应用写的快 而内核发送数据慢 需要把待发送数据写入缓冲区，而且设置了水位回调
 **/
/**
 * 发送数据 应用写的快 而内核发送数据慢 需要把待发送数据写入缓冲区，而且设置了水位回调
 *
 * 线程安全的发送逻辑：
 * 1. 如果连接已断开，直接返回
 * 2. 首次写入且outputBuffer_为空时，尝试直接write到socket
 * 3. 若数据未一次性发完，剩余部分追加到outputBuffer_
 * 4. 启用EPOLLOUT，等待Poller通知可写后继续发送
 *
 * 流量控制：
 * - 当outputBuffer_超过高水位时，调用highWaterMarkCallback_
 * - 防止应用写入速度远快于内核发送速度导致内存暴涨
 *
 * @param data 待发送数据首地址
 * @param len  待发送数据长度
 */
void TcpConnection::sendInLoop(const void *data, size_t len)
{
    ssize_t nwrote = 0;          // 已写入字节数
    size_t remaining = len;      // 剩余待发送字节数
    bool faultError = false;   // 是否发生致命错误

    // 如果连接已断开，不能继续发送
    if (state_ == kDisconnected)
    {
        LOG_ERROR << "disconnected, give up writing";
        return;
    }

    /* 情况1：channel尚未关注写事件，且发送缓冲区为空，尝试一次性write */
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = ::write(channel_->fd(), data, len);
        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            /* 若一次性发完且用户关注写完成事件，回调writeCompleteCallback_ */
            if (remaining == 0 && writeCompleteCallback_)
            {
                loop_->queueInLoop(
                    std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else // nwrote < 0
        {
            nwrote = 0; // 重置已写字节数
            /* EWOULDBLOCK（EAGAIN）表示TCP发送缓冲区满，不算致命错误 */
            if (errno != EWOULDBLOCK)
            {
                LOG_ERROR << "TcpConnection::sendInLoop";
                /* EPIPE: 对端关闭写端；ECONNRESET: 连接被对端重置 */
                if (errno == EPIPE || errno == ECONNRESET)
                {
                    faultError = true;
                }
            }
        }
    }

    /*
     * 情况2：数据未一次性发完，需要将剩余部分缓存到outputBuffer_
     * 注册EPOLLOUT事件，等Poller通知可写时，handleWrite会继续发送
     */
    if (!faultError && remaining > 0)
    {
        size_t oldLen = outputBuffer_.readableBytes();
        size_t newLen = oldLen + remaining;

        /* 超过高水位且首次触发，回调highWaterMarkCallback_做流控 */
        if (newLen >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_)
        {
            loop_->queueInLoop(
                std::bind(highWaterMarkCallback_, shared_from_this(), newLen));
        }

        // 将剩余数据追加到发送缓冲区
        outputBuffer_.append((char *)data + nwrote, remaining);

        // 如果channel未关注写事件，这里必须启用，否则Poller不会通知epollout
        if (!channel_->isWriting())
        {
            channel_->enableWriting();
        }
    }
}

/**
 * 关闭连接（半关闭）
 * 
 * 只关闭写端，不再发送数据，但仍可接收数据
 * 会等待outputBuffer_中的数据发送完毕后再关闭
 */
void TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);  // 设置状态为正在断开
        
        // 投递到IO线程执行实际的关闭操作
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, shared_from_this()));
    }
}

/**
 * 在IO线程中执行关闭操作
 * 
 * 半关闭流程：
 * 1. 确保outputBuffer_中的数据已发送完毕
 * 2. 调用socket的shutdownWrite关闭写端
 * 
 * 设计考虑：
 * - 必须等待数据发送完毕才能关闭
 * - 使用shared_from_this()确保生命周期安全
 */
void TcpConnection::shutdownInLoop()
{
    // 如果outputBuffer_中的数据已全部发送完毕
    if (!channel_->isWriting())
    {
        socket_->shutdownWrite();  // 关闭写端，发送FIN包
    }
    // 如果还有数据在发送，handleWrite会在发送完毕后继续关闭流程
}

/**
 * 连接建立完成
 * 
 * 由Acceptor调用，通知TcpConnection连接已建立
 * 
 * 执行流程：
 * 1. 设置连接状态为已连接
 * 2. 绑定Channel和TcpConnection的生命周期
 * 3. 启用读事件监听
 * 4. 调用用户连接回调
 */
void TcpConnection::connectEstablished()
{
    setState(kConnected);                    // 设置状态为已连接
    channel_->tie(shared_from_this());       // 绑定生命周期
    channel_->enableReading();               // 启用读事件监听

    // 调用用户连接回调
    connectionCallback_(shared_from_this());
}

/**
 * 连接销毁
 * 
 * 由EventLoop调用，清理连接资源
 * 
 * 执行流程：
 * 1. 如果还在连接状态，先断开连接
 * 2. 禁用所有事件监听
 * 3. 调用用户断开回调
 * 4. 从Poller中移除Channel
 */
void TcpConnection::connectDestroyed()
{
    if (state_ == kConnected)
    {
        setState(kDisconnected);           // 设置状态为已断开
        channel_->disableAll();            // 禁用所有事件
        connectionCallback_(shared_from_this());  // 调用用户回调
    }
    
    channel_->remove();  // 从Poller中移除Channel
}

// 读是相对服务器而言的 当对端客户端有数据到达 服务器端检测到EPOLLIN 就会触发该fd上的回调 handleRead取读走对端发来的数据
/**
 * 处理读事件
 * 
 * 当socket可读时调用，读取数据并调用用户回调
 * 
 * @param receiveTime: 数据接收时间戳
 */
void TcpConnection::handleRead(Timestamp receiveTime)
{
    int savedErrno = 0;
    
    // 从socket读取数据到inputBuffer_
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    
    if (n > 0)
    {
        // 读取到数据，调用用户消息回调
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)
    {
        // 对端关闭连接（收到FIN包）
        handleClose();
    }
    else
    {
        // 读取错误
        errno = savedErrno;
        LOG_ERROR<<"TcpConnection::handleRead";
        handleError();
    }
}

/**
 * 处理写事件
 * 
 * 当socket可写时调用，将outputBuffer_中的数据发送出去
 * 
 * 设计要点：
 * - 只在有数据需要发送时启用写事件
 * - 数据发送完毕后禁用写事件
 * - 支持写完成回调
 */
void TcpConnection::handleWrite()
{
    if (channel_->isWriting())
    {
        int savedErrno = 0;
        
        // 将outputBuffer_中的数据写入socket
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &savedErrno);
        
        if (n > 0)
        {
            // 成功发送数据，更新缓冲区
            outputBuffer_.retrieve(n);
            
            // 如果数据全部发送完毕
            if (outputBuffer_.readableBytes() == 0)
            {
                // 禁用写事件监听（避免busy loop）
                channel_->disableWriting();
                
                // 调用写完成回调
                if (writeCompleteCallback_)
                {
                    // 投递到EventLoop线程执行
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this()));
                }
                
                // 如果正在断开连接，继续关闭流程
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop();
                }
            }
        }
        else
        {
            // 写错误
            LOG_ERROR<<"TcpConnection::handleWrite";
        }
    }
    else
    {
        // 不应该到达这里，说明逻辑有问题
        LOG_ERROR<<"Connection fd = "<<channel_->fd()<<" is down, no more writing";
    }
}

/**
 * 处理连接关闭事件
 * 
 * 当对端关闭连接或发生错误时调用
 * 
 * 执行流程：
 * 1. 更新连接状态
 * 2. 禁用所有事件监听
 * 3. 调用用户连接回调
 * 4. 调用关闭回调（通知TcpServer移除连接）
 */
void TcpConnection::handleClose()
{
    LOG_INFO<<"TcpConnection::handleClose fd="<<channel_->fd()<<"state="<<(int)state_;
    
    setState(kDisconnected);        // 设置状态为已断开
    channel_->disableAll();         // 禁用所有事件

    TcpConnectionPtr connPtr(shared_from_this());
    
    connectionCallback_(connPtr);     // 执行连接关闭的用户回调
    closeCallback_(connPtr);        // 执行TcpServer::removeConnection，从服务器中移除连接
}

/**
 * 处理连接错误
 * 
 * 通过getsockopt获取socket错误码
 * 记录错误信息供调试
 */
void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    
    // 获取socket错误码
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;  // getsockopt失败
    }
    else
    {
        err = optval;  // 获取到的错误码
    }
    
    // 记录错误信息
    LOG_ERROR<<"TcpConnection::handleError name:"<<name_.c_str()<<"- SO_ERROR:%"<<err;
}

// 新增的零拷贝发送函数
void TcpConnection::sendFile(int fileDescriptor, off_t offset, size_t count) {
    if (connected()) {
        if (loop_->isInLoopThread()) { // 判断当前线程是否是loop循环的线程
            sendFileInLoop(fileDescriptor, offset, count);
        }else{ // 如果不是，则唤醒运行这个TcpConnection的线程执行Loop循环
            loop_->runInLoop(
                std::bind(&TcpConnection::sendFileInLoop, shared_from_this(), fileDescriptor, offset, count));
        }
    } else {
        LOG_ERROR<<"TcpConnection::sendFile - not connected";
    }
}

// 在事件循环中执行sendfile
void TcpConnection::sendFileInLoop(int fileDescriptor, off_t offset, size_t count) {
    ssize_t bytesSent = 0; // 发送了多少字节数
    size_t remaining = count; // 还要多少数据要发送
    bool faultError = false; // 错误的标志位

    if (state_ == kDisconnecting) { // 表示此时连接已经断开就不需要发送数据了
        LOG_ERROR<<"disconnected, give up writing";
        return;
    }

    // 表示Channel第一次开始写数据或者outputBuffer缓冲区中没有数据
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0) {
        bytesSent = sendfile(socket_->fd(), fileDescriptor, &offset, remaining);
        if (bytesSent >= 0) {
            remaining -= bytesSent;
            if (remaining == 0 && writeCompleteCallback_) {
                // remaining为0意味着数据正好全部发送完，就不需要给其设置写事件的监听。
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        } else { // bytesSent < 0
            if (errno != EWOULDBLOCK) { // 如果是非阻塞没有数据返回错误这个是正常显现等同于EAGAIN，否则就异常情况
                LOG_ERROR<<"TcpConnection::sendFileInLoop";
            }
            if (errno == EPIPE || errno == ECONNRESET) {
                faultError = true;
            }
        }
    }
    // 处理剩余数据
    if (!faultError && remaining > 0) {
        // 继续发送剩余数据
        loop_->queueInLoop(
            std::bind(&TcpConnection::sendFileInLoop, shared_from_this(), fileDescriptor, offset, remaining));
    }
}