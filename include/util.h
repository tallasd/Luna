#pragma once
#include <string>
#include <cstdio>
#include <cstdarg>		//va_list and stuff
#include <cstdlib>
#include "dmntcht.h"
#include "progressbar.hpp"
#include <thread>
#include <chrono>

#ifndef UTIL_H
#define UTIL_H


namespace util
{
    //removes char from C++ string
    void stripChar(char _c, std::string& _s);

    std::string getIslandName(u64 mainAddr);

    u64 FollowPointerMain(u64 pointer, ...);
}
#endif // UTIL_H
