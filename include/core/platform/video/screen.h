#pragma once
#include "types.h"
#include "util.h"
#include "../memory/memory.h"

#ifdef __cplusplus
extern "C" {
#endif

PResult pscreen_init();
PResult pscreen_deinit();

PHandle pscreen_get();

#ifdef __cplusplus
}
#endif
