/**
 * Poller抽象类实现
 * 
 * 设计目的：
 * - 提供统一的IO复用接口
 * - 支持epoll和poll两种实现
 * - 实现工厂模式，根据环境变量选择具体实现
 */

#include <Poller.h>
#include <Channel.h>

Poller::Poller(EventLoop *loop)
    : ownerLoop_(loop)
{
}

bool Poller::hasChannel(Channel *channel) const
{
    auto it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}