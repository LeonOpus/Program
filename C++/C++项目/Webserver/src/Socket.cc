/**
 * Socket封装类实现
 * 
 * 设计目的：
 * - 封装socket相关系统调用
 * - 提供RAII风格的socket管理
 * - 简化socket操作，提高代码可读性
 * - 自动处理错误情况
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#include <Socket.h>
#include <Logger.h>
#include <InetAddress.h>

/**
 * Socket析构函数
 * 
 * RAII风格：自动关闭socket文件描述符
 * 确保资源正确释放，避免文件描述符泄漏
 */
Socket::~Socket()
{
    ::close(sockfd_);
}

/**
 * 绑定地址
 * 
 * 将socket绑定到指定的本地地址
 * 
 * @param localaddr 本地地址
 */
void Socket::bindAddress(const InetAddress &localaddr)
{
    if (0 != ::bind(sockfd_, (sockaddr *)localaddr.getSockAddr(), sizeof(sockaddr_in)))
    {
        LOG_FATAL<<"bind sockfd:"<<sockfd_ <<"fail";
    }
}

/**
 * 开始监听
 * 
 * 将socket设置为监听状态，准备接受连接
 * 
 * 参数说明：
 * - backlog: 1024，表示等待连接队列的最大长度
 */
void Socket::listen()
{
    if (0 != ::listen(sockfd_, 1024))
    {
        LOG_FATAL<<"bind sockfd:"<<sockfd_ <<"fail";
    }
}

/**
 * 接受新连接
 * 
 * 从监听socket接受一个新的连接
 * 
 * @param peeraddr 输出参数，对端地址
 * @return 新连接的文件描述符，失败返回-1
 */
int Socket::accept(InetAddress *peeraddr)
{
    /**
     * 1. accept函数的参数不合法
     * 2. 对返回的connfd没有设置非阻塞
     * Reactor模型 one loop per thread
     * poller + non-blocking IO
     **/
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    ::memset(&addr, 0, sizeof(addr));
    // fixed : int connfd = ::accept(sockfd_, (sockaddr *)&addr, &len);
    int connfd = ::accept4(sockfd_, (sockaddr *)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
    }
    return connfd;
}

/**
 * 关闭写端
 * 
 * 发送FIN包，告知对端本端不再发送数据
 * 但还可以接收数据（半关闭状态）
 */
void Socket::shutdownWrite()
{
    if (::shutdown(sockfd_, SHUT_WR) < 0)
    {
        LOG_ERROR<<"shutdownWrite error";
    }
}

/**
 * 设置TCP_NODELAY选项
 * 
 * 禁用Nagle算法，减少小数据包的延迟
 * 适用于对延迟敏感的应用（如游戏、实时通信）
 * 
 * @param on: true表示禁用Nagle算法
 */
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

/**
 * 设置SO_REUSEADDR选项
 * 
 * 允许重用本地地址
 * 解决TIME_WAIT状态导致的地址绑定问题
 * 
 * @param on: true表示允许地址重用
 */
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

/**
 * 设置SO_REUSEPORT选项
 * 
 * 允许多个socket绑定到同一个端口
 * 实现负载均衡，提高多核CPU利用率
 * 
 * @param on: true表示允许端口重用
 */
void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

/**
 * 设置SO_KEEPALIVE选项
 * 
 * 启用TCP心跳检测机制
 * 检测对端是否异常断开连接
 * 
 * @param on: true表示启用心跳检测
 */
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}