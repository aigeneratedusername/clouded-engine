#define PLATFORM_INTERNAL
#include "core/platform/internal/internal.h"
#include "core/platform/memory/memory.h"

PResult palloc(PAllocator *allocator, size_t nbytes, size_t align, PAllocatorCapabilities requires) {
	PResult res = { 0 };
	void *out_ptr = NULL;

	if(!allocator || !allocator->alloc) { 
		res = PErr(PERROR_NULLPTR);
		goto out;
	}

	if(nbytes || align == 0) {
		res = PErr(PERROR_INVALID_PARAMS);
		goto out;
	}

	if((allocator->caps & requires) == requires) {
		out_ptr =  allocator->alloc(allocator->ctx, nbytes, align);
		res = POk_ptr(out_ptr);
	}

out: 
	return res;
}

PResult prealloc(PAllocator *allocator, void *ptr, size_t nbytes, size_t align, PAllocatorCapabilities requires) {
	PResult res = { 0 };
	void *out_ptr = NULL;

	if(!allocator || !allocator->realloc) {
		res = PErr(PERROR_NULLPTR);
		goto out;
	}

	if(nbytes == 0 || align == 0) {
		res = PErr(PERROR_INVALID_PARAMS);
		goto out;
	}

	if(!(allocator->caps & PALLOCATOR_CAP_SUPPORTS_REALLOC)) {
		res = PErr(PERROR_UNDEFINED); // TODO: add proper errors for bit flags
		goto out;
	}

	if((allocator->caps & requires) == requires) {
		out_ptr = allocator->realloc(allocator->ctx, ptr, nbytes, align);
		res = POk_ptr(out_ptr);
	}

out:
	return res;
}

PResult pfree(PAllocator *allocator, void *mem, PAllocatorCapabilities requires) {
	PResult res = { 0 };

	if(!allocator || !allocator->free || !mem) {
		res = PErr(PERROR_NULLPTR);
		goto out;
	}

	if(!(allocator->caps & PALLOCATOR_CAP_SUPPORTS_INDIVIDUAL_FREE)) {
		res = PErr(PERROR_UNDEFINED);
		goto out;
	}

	if((allocator->caps & requires) == requires) {
		allocator->free(allocator->ctx, mem);
		res = POk_int(0);
	}

out:
	return res;
}
