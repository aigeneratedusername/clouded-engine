#pragma once
#include "core/memory/memory.hpp"
#include "core/platform/platform.h"
#include "core/renderer/renderer.hpp"
#include "core/result.hpp"
#include "core/types.hpp"
#include "core/util.hpp"
#include "runtime/runtime.hpp"

PResult eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbin_path);
