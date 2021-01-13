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

extern const s64 SaveHeaderSize;

extern const u64 mainSize;
extern const u64 GSavePlayerVillagerAccountOffset;
extern const u64 GSavePlayerVillagerAccountSize;
extern const u64 playerSize;
extern const u64 playersOffset;

//taken from NHSE
extern const u64 PersonalID;
extern const u64 houseSize;
extern const u64 houseOffset;
extern const u64 EventFlagOffset;
extern const u64 StorageSizeOffset;
extern const u64 Pocket2SizeOffset;

struct IslandName {
    u16 name[0xB];
};

namespace util
{

    std::string safeString(const std::string& s);

    //removes char from C++ string
    void stripChar(char _c, std::string& _s);

    std::string getIslandNameASCII(u64 playerAddr);

    std::string getDreamAddrString(u64 mainAddr);

    TimeCalendarTime getDreamTime(u64 mainAddr);

    IslandName getIslandName(u64 playerAddr);

    u64 FollowPointerMain(u64 pointer, ...);

    std::string GetLastTimeSaved(u64 mainAddr);
}
#endif // UTIL_H
