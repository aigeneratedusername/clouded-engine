#define PLATFORM_INTERNAL
#include "core/platform/internal/memory.h"

static pu8 				memory[PINTERNALMEM_SIZE];
static PIMemAllocator 	allocator;

PResult pimeminit() {
	allocator.buffer = memory;
	allocator.capacity = PINTERNALMEM_SIZE;
	allocator.offset = 0;

	return POk_int(0);
}

PResult pialloc(size_t nbytes, size_t align) {
	PResult res = { 0 };
	
	if(align == 0 || (align & (align - 1)) != 0) {
		res = PErr(PERROR_BAD_ALIGN);
		goto out;
	}
	
	size_t aligned_offset = (allocator.offset + align - 1) & ~(align - 1);

	if(aligned_offset + nbytes > allocator.capacity) {
		res = PErr(PERROR_OUT_OF_MEMORY);
		goto out;
	}

	void *next_free_addr = allocator.buffer + aligned_offset;
	allocator.offset = aligned_offset + nbytes;
	res = POk_ptr(next_free_addr);
out:
	return res;
}

size_t pialloc_used() {
	return allocator.offset;
}
