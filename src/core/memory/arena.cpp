#include "core/memory/arena.hpp"

PAllocatorCapabilities MemArenaCapabilities = {};

EResult memarena_init(const pu8 *membuffer, size_t size) {
	EResult res = {};
	MemArena *memarena = nullptr;

	if(size < sizeof(MemArena)) {
		res	= EErr(EERROR_DOMAIN_MEMORY, EERROR_OUT_OF_MEMORY);
		goto out;
	}

	memarena = (MemArena*) membuffer;
	memarena->capacity = size - sizeof(MemArena);
	memarena->offset = 0;
	res = EOk_ptr(memarena);
out:
	return res;
}

EResult memarena_deinit(MemArena **memarena) {
	return EOk_int(0);
}

void *memarena_alloc(void *memarena, size_t nbytes, size_t alignment) {
	if(!memarena || nbytes == 0 || alignment == 0) 
		return nullptr;
	MemArena *arena = (MemArena*) memarena;

	size_t aligned_off = PALIGN_UP(arena->offset, alignment);
	if(aligned_off > arena->capacity || 
		nbytes > arena->capacity - aligned_off) {
		return nullptr;
	}

	arena->offset = aligned_off + nbytes;
	printf("Successfully alloced %zu bytes.\n", nbytes); // TODO: replace with LOG_DEBUG and logging functionality 
	return (pu8*) arena + sizeof(MemArena) + aligned_off;
}

EResult memarena_reset(MemArena &memarena) {
	memarena.offset = 0;
	return EOk_int(0);
}

PAllocator memarena_make_pallocator(MemArena &memarena) {
	return {
		.ctx = (void*) &memarena,
		.alloc = memarena_alloc,
		.realloc = nullptr,
		.free = nullptr,
		.caps = MemArenaCapabilities
	};
}
