#include "core/memory/arena.hpp"

PAllocatorCapabilities MemArenaCapabilities = {};

PResult memarena_init(const pu8 *membuffer, size_t size) {
	PResult res = {};
	MemArena *memarena = nullptr;

	if(size < sizeof(MemArena)) {
		res	 = PErr(PERROR_OUT_OF_MEMORY);
	}

	return res;
}

PResult memarena_deinit(MemArena **memarena) {
	return POk_int(0);
}

void *memarena_alloc(void *memarena, size_t nbytes, size_t alignment) {
	if(!memarena || nbytes == 0 || alignment == 0)
		return NULL;
	MemArena *arena = (MemArena*) memarena;

	return NULL;
}

PResult memarena_reset(MemArena &memarena) {
	memarena.offset = 0;
	return POk_int(0);
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
