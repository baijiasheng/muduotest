#pragma once

#include <functional>
#include "NonCopyable.h"
#include "Socket.h"
#include "Channel.h"

class EventLoop;
class InetAddress;

using namespace std;
using NewConnectionCallback = function<void(int sockfd, const InetAddress &address)>;

class Acceptor : NonCopyable
{
public:
    Acceptor();
    ~Acceptor();

    void set_new_connection_callback(const NewConnectionCallback &cb)  //设置一个连接回调
    {
        new_connetion_callback_ = cb;
    }

    bool is_listening() { return listenning_; } //判断是否连接

    void listen();

private:
    void handle_read();

private:
    EventLoop *loop_; //acceptor用的用户定义的那个baseloop，也就是mainloop

    Socket accept_socket_;
    Channel accept_channel_;

    NewConnectionCallback new_connetion_callback_;

    bool listenning_;
};