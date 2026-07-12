#pragma once
#include "types.h"
#include "util.h"
#include "../memory/memory.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct PSystem PSystem;

PResult psystem_init();
PResult psystem_deinit();

#ifdef __cplusplus
}
#endif
