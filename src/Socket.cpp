#include <strings.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include "Socket.h"
#include "Logger.hpp"
#include "InetAddress.h"

Socket::~Socket()
{
    close(sockfd_);
}

void Socket::bind_address(const InetAddress &loacladdr)
{
    if (bind(sockfd_, (sockaddr *)loacladdr.get_sockaddr(), sizeof(sockaddr_in)) != 0)
    {
        perror("bind sockfd:%d fail \n");
    }
}

void Socket::listen()
{
    if (::listen(sockfd_, 1024) != 0)
    {
        perror("listen sockfd:%d fail \n");
    }
}

int Socket::accept(InetAddress *peeraddr)
{
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    socklen_t len = sizeof(addr);
    int connfd = ::accept4(sockfd_, (sockaddr *)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->set_sockaddr(addr);
    }
    return connfd;
}

void Socket::shutdown_write()
{
    if (::shutdown(sockfd_, SHUT_WR) < 0)
    {
        perror("shutdown write error");
    }
}

void Socket::set_tcp_noDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

void Socket::set_reuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void Socket::set_reusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::set_keepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}