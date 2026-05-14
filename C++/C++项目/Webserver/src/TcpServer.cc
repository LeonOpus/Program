/**
 * TcpServer：TCP服务器实现
 * 
 * 设计目的：
 * - 管理多个TCP连接
 * - 实现主从Reactor模式
 * - 提供简洁的服务器接口
 * - 支持多线程并发处理
 * 
 * 架构特点：
 * - 主线程负责接受新连接（mainReactor）
 * - 工作线程处理IO事件（subReactor）
 * - 每个连接对应一个TcpConnection对象
 */

#include <functional>
#include <string.h>

#include <TcpServer.h>
#include <Logger.h>
#include <TcpConnection.h>
#include <cassert>

static EventLoop *CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL<<"main Loop is NULL!";
    }
    return loop;
}

/**
 * TcpServer构造函数
 * 
 * 初始化TCP服务器：
 * 1. 校验主EventLoop非空
 * 2. 创建Acceptor用于接受新连接
 * 3. 创建EventLoopThreadPool管理工作线程
 * 4. 设置新连接回调
 * 
 * @param loop: 主EventLoop（mainReactor）
 * @param listenAddr: 监听地址
 * @param nameArg: 服务器名称
 * @param option: 选项（是否启用端口重用）
 */
TcpServer::TcpServer(EventLoop *loop,
                     const InetAddress &listenAddr,
                     const std::string &nameArg,
                     Option option)
    : loop_(CheckLoopNotNull(loop))               // 主EventLoop，不能为空
    , ipPort_(listenAddr.toIpPort())              // 监听地址字符串
    , name_(nameArg)                              // 服务器名称
    , acceptor_(new Acceptor(loop, listenAddr, option == kReusePort))  // Acceptor
    , threadPool_(new EventLoopThreadPool(loop, name_))  // 线程池
    , connectionCallback_()                       // 连接回调（用户设置）
    , messageCallback_()                          // 消息回调（用户设置）
    , nextConnId_(1)                              // 连接ID计数器
    , started_(0)                                 // 启动标志
{
    // 设置Acceptor的新连接回调
    // 当有新连接时，Acceptor会调用TcpServer::newConnection
    acceptor_->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

/**
 * TcpServer析构函数
 * 
 * 清理所有连接：
 * 1. 遍历所有连接
 * 2. 在每个连接的IO线程中销毁连接
 * 
 * 设计考虑：
 * - 必须在对应的IO线程中销毁连接
 * - 使用shared_ptr管理连接生命周期
 * - 确保资源正确释放
 */
TcpServer::~TcpServer()
{
    for(auto &item : connections_)
    {
        TcpConnectionPtr conn(item.second);
        item.second.reset();    // 把原始的智能指针复位 让栈空间的TcpConnectionPtr conn指向该对象 当conn出了其作用域 即可释放智能指针指向的对象
        // 销毁连接
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed, conn));
    }
}

/**
 * 设置工作线程数量
 * 
 * @param numThreads: 工作线程数量（0表示单线程模式）
 * 
 * 线程模型：
 * - 0：单线程模式，所有连接都在主线程处理
 * - N：多线程模式，N个工作线程处理连接
 */
void TcpServer::setThreadNum(int numThreads)
{
    assert(0 <= numThreads);
    threadPool_->setThreadNum(numThreads);
}

/**
 * 启动TCP服务器
 * 
 * 启动流程：
 * 1. 启动工作线程池
 * 2. 启动Acceptor监听
 * 
 * 线程安全：
 * - 使用原子变量确保只启动一次
 * - 必须在主线程中调用
 */
void TcpServer::start()
{
    if (started_.fetch_add(1) == 0)    // 原子操作，确保只启动一次
    {
        threadPool_->start(threadInitCallback_);    // 启动底层的loop线程池
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));  // 在主线程中启动Acceptor监听
    }
}

/**
 * 处理新连接
 * 
 * 新连接处理流程：
 * 1. 选择一个工作线程（轮询算法）
 * 2. 生成连接名称（服务器名+IP端口+连接ID）
 * 3. 获取本地地址
 * 4. 创建TcpConnection对象
 * 5. 设置连接回调
 * 6. 建立连接
 * 
 * @param sockfd: 新连接的socket文件描述符
 * @param peerAddr: 对端地址
 */
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    // 轮询算法 选择一个subLoop 来管理connfd对应的channel
    EventLoop *ioLoop = threadPool_->getNextLoop();
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;  // 这里没有设置为原子类是因为其只在mainloop中执行 不涉及线程安全问题
    std::string connName = name_ + buf;

    LOG_INFO<<"TcpServer::newConnection ["<<name_.c_str()<<"]- new connection ["<<connName.c_str()<<"]from "<<peerAddr.toIpPort().c_str();
    
    // 通过sockfd获取其绑定的本机的ip地址和端口信息
    sockaddr_in local;
    ::memset(&local, 0, sizeof(local));
    socklen_t addrlen = sizeof(local);
    if(::getsockname(sockfd, (sockaddr *)&local, &addrlen) < 0)
    {
        LOG_ERROR<<"sockets::getLocalAddr";
    }

    InetAddress localAddr(local);
    TcpConnectionPtr conn(new TcpConnection(ioLoop,
                                            connName,
                                            sockfd,
                                            localAddr,
                                            peerAddr));
    connections_[connName] = conn;
    // 下面的回调都是用户设置给TcpServer => TcpConnection的，至于Channel绑定的则是TcpConnection设置的四个，handleRead,handleWrite... 这下面的回调用于handlexxx函数中
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);

    // 设置了如何关闭连接的回调
    conn->setCloseCallback(
        std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));

    // 建立连接（必须在TcpConnection的IO线程中执行）
    ioLoop->runInLoop(
        std::bind(&TcpConnection::connectEstablished, conn));
}

/**
 * 移除连接（线程安全接口）
 * 
 * 设计考虑：
 * - 可能在任何线程中调用
 * - 必须在主线程中执行实际的移除操作
 * - 使用runInLoop确保线程安全
 * 
 * @param conn: 要移除的连接
 */
void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    // 确保在主线程中执行移除操作
    loop_->runInLoop(
        std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

/**
 * 在IO线程中移除连接
 * 
 * 移除流程：
 * 1. 从connections_中移除连接
 * 2. 在连接的IO线程中销毁连接
 * 
 * 线程安全：
 * - 必须在主线程中调用
 * - 连接的销毁在对应的IO线程中执行
 * 
 * @param conn: 要移除的连接
 */
void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    LOG_INFO<<"TcpServer::removeConnectionInLoop ["<<
             name_.c_str()<<"] - connection %s"<<conn->name().c_str();

    connections_.erase(conn->name());
    EventLoop *ioLoop = conn->getLoop();
    ioLoop->queueInLoop(
        std::bind(&TcpConnection::connectDestroyed, conn));
}