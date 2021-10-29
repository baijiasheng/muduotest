#pragma once

#include <memory>
#include <functional>
#include "TimeStamp.h"

class Buffer;
class TcpConnection;

using namespace std;  //设置函数回调

using TcpConnectionPtr = shared_ptr<TcpConnection>;
using ConnectionCallback = function<void(const TcpConnectionPtr &)>;
using CloseCallback = function<void(const TcpConnectionPtr &)>;
using WriteCompleteCallback = function<void(const TcpConnectionPtr &)>;

using MessageCallback = function<void(const TcpConnectionPtr &, Buffer *, TimeStamp)>;

using HighWaterMarkCallback = function<void(const TcpConnectionPtr &, size_t)>;
