#pragma once 
#include "../platform/memory/memory.h"
#include "../types.hpp"

struct MemArena {
	size_t 	capacity;
	size_t 	offset;
};

extern PAllocatorCapabilities MemArenaCapabilities;

PResult memarena_init(const pu8 *membuffer, size_t size);
PResult memarena_deinit(MemArena **memarena);

void 	*memarena_alloc(void *memarena, size_t nbytes, size_t alignment);
PResult memarena_reset(MemArena &memarena);

PAllocator memarena_make_pallocator(MemArena &memarena);
