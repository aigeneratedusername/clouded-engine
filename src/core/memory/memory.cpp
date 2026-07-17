#include "core/memory/memory.hpp"

PSlice memtake_front(MemCursor *memory, size_t nbytes) {
	assert(nbytes <= memory->len);

	PSlice mem = {
		.ptr = memory->ptr,
		.len = nbytes
	};

	memory->ptr += nbytes;
	memory->len -= nbytes;
	return mem;
}
