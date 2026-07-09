#pragma once
#include "audio/audio.h"
#include "display/display.h"
#include "io/io.h"
#include "memory/memory.h"
#include "system/system.h"
#include "types.h"
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

PResult pinit();
PResult pdeinit();

#ifdef __cplusplus
}
#endif
