#include "core/memory/arena.hpp"

PAllocatorCapabilities MemArenaCapabilities = {};

EResult memarena_init(const pu8 *membuffer, size_t size) {
	EResult res = {};
	MemArena *memarena = nullptr;

	if(size < sizeof(MemArena)) {
		res	= EErr(EERROR_DOMAIN_MEMORY, EERROR_OUT_OF_MEMORY);
	}

	return res;
}

EResult memarena_deinit(MemArena **memarena) {
	return EOk_int(0);
}

void *memarena_alloc(void *memarena, size_t nbytes, size_t alignment) {
	if(!memarena || nbytes == 0 || alignment == 0)
		return NULL;
	MemArena *arena = (MemArena*) memarena;

	return NULL;
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
