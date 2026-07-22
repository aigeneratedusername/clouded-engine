#pragma once
#include "types.h"
#include "util.h"
#include "../memory/memory.h"

#ifdef __cplusplus
extern "C" {
#endif

PResult pscreen_init();
PResult pscreen_deinit();

PResult pscreen_get_size(pu32 *width, pu32 *height);
PHandle pscreen_get();

#ifdef __cplusplus
}
#endif
