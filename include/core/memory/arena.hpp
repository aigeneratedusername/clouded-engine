#pragma once 
#include "../platform/memory/memory.h"
#include "../types.hpp"

enum MemArenaError {
	MEMARENA_ERROR_ALLOC_FAILURE,
	MEMARENA_ERROR_BAD_ALIGNMENT
};

struct MemArena {
	size_t 	capacity;
	size_t 	offset;
};

extern PAllocatorCapabilities MemArenaCapabilities;

EResult memarena_init(const pu8 *membuffer, size_t size);
EResult memarena_deinit(MemArena **memarena);

void 	*memarena_alloc(void *memarena, size_t nbytes, size_t alignment);
EResult memarena_reset(MemArena &memarena);

PAllocator memarena_make_pallocator(MemArena &memarena);
