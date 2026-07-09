#pragma once
#ifndef PLATFORM_INTERNAL
	#error "platform/internal/memory.h is internal and must not be included directly."
#endif

#define PLATFORM_INTERNAL
#include "types.h"
#include "util.h"
#undef PLATFORM_INTERNAL
#include "../memory/util.h"

#define PINTERNALMEM_SIZE 	PKB(256)

PResult pimeminit();
PResult pialloc(size_t nbytes, size_t align);
size_t 	pialloc_used();
