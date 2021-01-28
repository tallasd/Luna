#include "util.h"

extern const s64 SaveHeaderSize = 0x110;

extern const u64 mainSize = 0x504360; //changed in 1.7.0
extern const u64 GSavePlayerVillagerAccountOffset = 0x1E2280 - 0x110;
extern const u64 GSavePlayerVillagerAccountSize = 0x48;
extern const u64 DreamIDOffset = 0x502EA8; //changed in 1.7.0
extern const u64 DreamInfoSize = 0x50;


extern const u64 playerSize = 0x36930;
extern const u64 playersOffset = 0x7A858; //changed in 1.7.0

//taken from NHSE
//*personal.dat*//
extern const u64 PersonalID = 0xAFA8;
extern const u64 StorageSizeOffset = 0x4081C; //absolute file offset //changed in 1.7.0
extern const u64 Pocket2SizeOffset = 0x36B00; //absolute file offset //changed in 1.7.0

//*main.dat*//
extern const u64 houseSize = 0x26400;
extern const u64 houseLvlOffset = 0x2E5634; //changed in 1.7.0
extern const u64 EventFlagOffset = 0x20A408; //changed in 1.7.0

static const char verboten[] = { ',', '/', '\\', '<', '>', ':', '"', '|', '?', '*', '™', '©', '®' };

static bool isVerboten(const u16& t)
{
    for (unsigned i = 0; i < 13; i++)
    {
        if (t == verboten[i])
            return true;
    }

    return false;
}

static inline bool isASCII(const u16& t)
{
    return (t > 31 && t < 127);
}


std::string util::getIslandNameASCII(u64 playerAddr)
{
    //0x16 byte = 0xB wide-chars/uint_16
    u16 name[0xB] = { 0 };
    u16 namechar;

    for (u8 i = 0; i < 0xB; i++) {
        dmntchtReadCheatProcessMemory(playerAddr + PersonalID + 0x4 + (i * 0x2), &namechar, 0x2);
        //make sure we can use this fuck string in a path
        if (isASCII(namechar) && !isVerboten(namechar)) {
            name[i] = namechar;
        }
        else {
            name[i] = 0x0000;
        }
    }
    //nullterminator pain
    u8 name_string[0x16] = { 0 };
    //pain
    utf16_to_utf8(name_string, name, sizeof(name_string) / sizeof(u8));

    return std::string((char*)name_string);
}


std::string util::getDreamAddrString(u64 mainAddr)
{
    u64 cDreamID = 0x0;
    char buffer[0x10] = { 0 };


    dmntchtReadCheatProcessMemory(mainAddr + DreamIDOffset, &cDreamID, sizeof(u64));
    sprintf(buffer, "%012li", cDreamID);

    std::string str1 = std::string(buffer).substr(0, 4);
    std::string str2 = std::string(buffer).substr(4, 4);
    std::string str3 = std::string(buffer).substr(8, 4);

    return std::string(str1 + "-" + str2 + "-" + str3);
}

TimeCalendarTime util::getDreamTime(u64 mainAddr)
{
    TimeCalendarTime dreamtime;
    u64 DreamTimeOffs = DreamIDOffset + 0x40;
    dmntchtReadCheatProcessMemory(mainAddr + DreamTimeOffs, &dreamtime, sizeof(TimeCalendarTime));
    return dreamtime;
}


IslandName util::getIslandName(u64 playerAddr)
{
    //0x16 byte = 0xB wide-chars/uint_16
    u16 name[0xB];

    dmntchtReadCheatProcessMemory(playerAddr + PersonalID + 0x4, name, 0x16);
    IslandName ret;
    memcpy(ret.name, name, sizeof(name));

    return ret;
}

void util::stripChar(char _c, std::string& _s)
{
    size_t pos = 0;
    while ((pos = _s.find(_c)) != _s.npos)
        _s.erase(pos, 1);
}


/**
 * @brief Follow a variable pointer path from main (last arg has to be 0xFFFFFFFFFFFFFFFF)
 */
u64 util::FollowPointerMain(u64 pointer, ...)
{
    u64 offset;
    va_list pointers;
    va_start(pointers, pointer);

    DmntCheatProcessMetadata metadata;
    dmntchtGetCheatProcessMetadata(&metadata);

    size_t bufferSize = sizeof offset;
    dmntchtReadCheatProcessMemory(metadata.main_nso_extents.base + pointer, &offset, bufferSize); // since the inital pointer will be a valid offset(we assumme anyways...) do a read64 call to it and store in offset
    //return 0xFFFFFFFFFFFFFFFF;
    pointer = va_arg(pointers, u64); // go to next argument
    while (pointer != 0xFFFFFFFFFFFFFFFF) // the last arg needs to be -1 in order for the while loop to exit
    {
        dmntchtReadCheatProcessMemory(pointer + offset, &offset, bufferSize);
        //return 0xFFFFFFFFFFFFFFFF;
        pointer = va_arg(pointers, u64);
    }
    va_end(pointers);
    return offset;
}


std::string util::GetLastTimeSaved(u64 mainAddr)
{
    const char* date_format = "%02d.%02d.%04d @ %02d-%02d";
    char ret[128];
    TimeCalendarTime time;
    dmntchtReadCheatProcessMemory(mainAddr + 0x504D20, &time, 0x8);
    sprintf(ret, date_format, time.day, time.month, time.year, time.hour, time.minute);
    return (std::string(ret));

}

