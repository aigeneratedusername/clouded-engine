#pragma once
#include "types.h"
#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

PResult 	palloc(PAllocator *allocator, size_t nbytes, size_t align, PAllocatorCapabilities requires);
PResult 	prealloc(PAllocator *allocator, void *ptr, size_t nbytes, size_t align, PAllocatorCapabilities requires);
PResult  	pfree(PAllocator *allocator, void *mem, PAllocatorCapabilities requires);

PResult 	pmemory_init(const PMemoryConfig memconf);
PResult 	pmemory_deinit(const PMemoryConfig memconf);

#ifdef __cplusplus
}
#endif
