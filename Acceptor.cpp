#include <sys/types.h>
#include <sys/socket.h>
#include "InetAddress.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "Logger.hpp"

Acceptor::~Acceptor()
{
}

static int create_sockfd()
{
    int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (sockfd == -1)
    {
	    perror("creat socket error");
		return false;
    }
    return sockfd;
}

void Acceptor::listen()
{
    listenning_ = true;
    accept_socket_.listen();

    accept_channel_.enable_reading();
    
}

void Acceptor::handle_read()
{
    InetAddress peeraddr; //获取地址

    int connfd = accept_socket_.accept(&peeraddr);
    if (connfd > 0)  //接受连接成功
    {
        if (new_connetion_callback_)
        {
            new_connetion_callback_(connfd, peeraddr); //轮询找到subloop，唤醒，分发当前新客户端的channel
        }
        else
        {
            close(connfd);
        }
    }
    else
    {
        perror("accept error");
    }
}