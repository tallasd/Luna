#include "util.h"


std::string util::getIslandName(u64 mainAddr)
{
    //0x16 byte = 0xB wide-chars/uint_16
    u16 name[0xB];
    u64 IslandNameOffset = 0x18;

    dmntchtReadCheatProcessMemory(mainAddr + IslandNameOffset, name, 0x16);

    u8 name_string[0x16];
    //pain
    utf16_to_utf8(name_string, name, sizeof(name_string) / sizeof(u8));

    return std::string((char*)name_string);
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

