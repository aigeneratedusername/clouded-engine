#pragma once
#include "core/platform/platform.h"
#include "core/renderer/renderer.hpp"
#include "core/types.hpp"
#include "core/util.hpp"

PResult eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbin_path);
