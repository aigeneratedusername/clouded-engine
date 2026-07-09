#pragma once
#ifndef PLATFORM_INTERNAL
	#error "platform/internal/types.h is internal and must not be included directly."
#endif

#include "../types.h"

typedef struct {
	pu8 	*buffer;
	size_t 	capacity;
	size_t 	offset;
} PIMemAllocator;
