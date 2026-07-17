#include "core/memory/arena.hpp"

PAllocatorCapabilities MemArenaCapabilities = {};

EResult memarena_init(const pu8 *membuffer, size_t size) {
	EResult res = {};
	MemArena *memarena = nullptr;

	if(size > sizeof(MemArena) + size) {
		res	= EErr(EERROR_DOMAIN_MEMORY, EERROR_OUT_OF_MEMORY);
		printf("failed here?\n");
		goto out;
	}

	memarena = (MemArena*)membuffer;
	memarena->capacity = size;
	memarena->offset = sizeof(MemArena);
	res = EOk_ptr(memarena);
out:
	return res;
}

EResult memarena_deinit(MemArena **memarena) {
	return EOk_int(0);
}

void *memarena_alloc(void *memarena, size_t nbytes, size_t alignment) {
	if(!memarena || nbytes == 0 || alignment == 0) {
		printf("%p\n %zu\n %zu\n", memarena, nbytes, alignment);
		return NULL;
	}
	MemArena *arena = (MemArena*) memarena;
	pu8 *out_addr = nullptr;

	size_t aligned_off = PALIGN_UP(arena->offset, alignment);
	if(aligned_off > arena->capacity) {
		printf("fucker\n");
		out_addr = (pu8*)1; //TODO: add a error ptr
		goto out;
	}

	arena->offset = aligned_off;
	out_addr = (pu8*) arena + aligned_off;
	printf("Successfully alloced %zu bytes.\n", nbytes);
out:
	return out_addr;
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
