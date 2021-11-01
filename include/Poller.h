#pragma once
#include "NonCopyable.h"
#include "Channel.h"
#include <vector>
#include <unordered_map>

class EventLoop;

using ChannelList = vector<Channel *>;
using ChannelMap = unordered_map<int, Channel *>;

class Poller : NonCopyable
{
public:
    Poller(EventLoop *loop);

    virtual ~Poller() = default;

    virtual TimeStamp poll(int timeout, ChannelList *active_channels) = 0;

    //判断channel是否在当前poller中
    bool has_channel(Channel *channel) const;

    //获取这个事件循环的poller
    static Poller *new_defaultPoller(EventLoop *loop);

    virtual void update_channel(Channel *channel) = 0;
    virtual void remove_channel(Channel *channel) = 0;

protected:
    ChannelMap channels_;

private:
    EventLoop *owner_loop_;
};
