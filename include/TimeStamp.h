#pragma once

#include <string>
#include <iostream>
using namespace std;

class TimeStamp
{
public:
    TimeStamp();
    explicit TimeStamp(int64_t times);

    static TimeStamp now();  //当前时间

    string to_string();

private:
    int64_t times_;
};