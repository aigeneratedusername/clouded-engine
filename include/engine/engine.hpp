#pragma once
#include "platform/platform.h"
#include "data_structures.hpp"
#include "gfx/gfx.hpp"
#include "types.hpp"
#include "util.hpp"

pi32 eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbin_path);
