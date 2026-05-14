#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <Acceptor.h>
#include <Logger.h>
#include <InetAddress.h>

// 创建非阻塞的监听socket
// SOCK_NONBLOCK: 设置为非阻塞模式，避免accept阻塞
// SOCK_CLOEXEC: 执行exec时自动关闭，防止文件描述符泄露
static int createNonblocking()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0)
    {
        LOG_FATAL << "listen socket create err " << errno;
    }
    return sockfd;
}

// Acceptor构造函数：负责监听新连接
// loop: 所属的事件循环（通常是主循环）
// listenAddr: 服务器监听的地址和端口
// reuseport: 是否启用SO_REUSEPORT选项，允许多个socket绑定到同一端口
Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
    : loop_(loop) // 保存事件循环指针
      ,
      acceptSocket_(createNonblocking()) // 创建监听socket
      ,
      acceptChannel_(loop, acceptSocket_.fd()) // 为监听socket创建Channel对象
      ,
      listenning_(false) // 初始状态：未开始监听
{
    // 设置socket选项：地址重用和端口重用
    // SO_REUSEADDR: 允许重用本地地址，服务器重启时快速绑定端口
    // SO_REUSEPORT: 多个线程/进程可以绑定到同一端口，实现负载均衡
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(true);

    // 绑定监听地址和端口
    acceptSocket_.bindAddress(listenAddr);

    // 设置Channel的读事件回调函数
    // 当有新连接到达时，监听socket变为可读，触发handleRead回调
    // 这个回调负责接受新连接并分发到工作线程
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
    acceptChannel_.disableAll(); // 把从Poller中感兴趣的事件删除掉
    acceptChannel_.remove();     // 调用EventLoop->removeChannel => Poller->removeChannel 把Poller的ChannelMap对应的部分删除
}

void Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_.listen();         // listen
    acceptChannel_.enableReading(); // acceptChannel_注册至Poller !重要
}

// listenfd有事件发生了，就是有新用户连接了
void Acceptor::handleRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (NewConnectionCallback_)
        {
            NewConnectionCallback_(connfd, peerAddr); // 轮询找到subLoop 唤醒并分发当前的新客户端的Channel
        }
        else
        {
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR << "accept Err";
        if (errno == EMFILE)
        {
            LOG_ERROR << "sockfd reached limit";
        }
    }
}