#pragma once
#ifndef PLATFORM_INTERNAL
	#error "platform/internal.h is internal and must not be included directly."
#endif

#define PLATFORM_INTERNAL
#include "memory.h"
#include "types.h"
#include "util.h"
#undef PLATFORM_INTERNAL

PResult pinternal_init();
PResult pinternal_deinit();
