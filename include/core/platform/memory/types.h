#pragma once
#include "../types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief Function pointer to an allocator alloc function
 * @see PAllocator
 */
typedef void *(*pallocFn)(void *ctx, size_t size, size_t alignment);
/** 
 * @brief Function pointer to an allocator realloc function 
 * @see PAllocator
 */
typedef void *(*preallocFn)(void *ctx, void *ptr, size_t size, size_t alignment);
/** 
 * @brief Function pointer to an allocator free function 
 * @see PAllocator
 */
typedef void  (*pfreeFn)(void *ctx, void *ptr);

/**
 * @brief Capabilities of an allocator
 * @see PAllocator
 */
typedef enum {
	PALLOCATOR_CAP_ZERO_ON_ALLOC				= 1 << 0,	/**< Memory is guaranteed to be zeroed out. */
	PALLOCATOR_CAP_SUPPORTS_REALLOC 			= 1 << 1, 	/**< Allocator supports realloc */
	PALLOCATOR_CAP_SUPPORTS_INDIVIDUAL_FREE 	= 1 << 2 	/**< Allocator supports freeing individual blocks */
} PAllocatorCapabilities;

/**  
 * @brief Interface for custom allocators
 */
typedef struct {
	void 						*ctx; 		/**< Allocator context pointer */
	pallocFn 					alloc;		/**< Allocator alloc function */
	preallocFn 					realloc;	/**< Allocator realloc function */
	pfreeFn 					free;		/**< Allocator free function */
	PAllocatorCapabilities 		caps;		/**< Allocator capabilities */
} PAllocator;

typedef enum {
	PMEMORY_REGION_DEFAULT = 0,
	PMEMORY_REGION_CONTIGUOUS,
	PMEMORY_REGION_INVALID
} PMemoryRegionType;

typedef struct {
	pu8 						*memory;
	size_t 						size;
	PMemoryRegionType			type;
	char 						name[8];
} PMemoryRegion;

typedef struct {
	PMemoryRegion 				*regions;
	size_t 						nregions;
} PMemoryLayout;

typedef struct {
	size_t 						region_size;
	PMemoryRegionType			region_type;
	char 						region_name[8];
} PMemoryConfigEntry;

typedef struct {
	const PMemoryConfigEntry 	*entries;
} PMemoryConfig;

#define PMEMORYCONFIG_END { 0, PMEMORY_REGION_INVALID, "CONFEND" }

#ifdef __cplusplus
}
#endif
