#pragma once
#include "progressbar.hpp"
#include "log.hpp"
#include <vector>
#include <util.h>
#include <cstring>
#include <string>
#include "luna.h"
#include <sys/stat.h>
#include "file.h"		//read and write stuff


void Dumper(u8 *progress, const char **status, tsl::elm::Log** logelm);