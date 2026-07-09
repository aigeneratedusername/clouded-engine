#pragma once
#include "../types.h"
#include "../util.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct PAudio PAudio;

PResult paudio_init();
PResult paudio_deinit();

#ifdef __cplusplus
}
#endif
