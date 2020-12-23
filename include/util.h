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

struct IslandName {
    u16 name[0xB];
};

namespace util
{

    std::string safeString(const std::string& s);

    //removes char from C++ string
    void stripChar(char _c, std::string& _s);

    std::string getIslandNameASCII(u64 mainAddr);

    std::string getDreamAddrString(u64 mainAddr);

    TimeCalendarTime getDreamTime(u64 mainAddr);

    IslandName getIslandName(u64 mainAddr);

    u64 FollowPointerMain(u64 pointer, ...);

    std::string GetLastTimeSaved(u64 mainAddr);
}
#endif // UTIL_H
