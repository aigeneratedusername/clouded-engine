#include "platform/memory.h"
#include <3ds.h>

pu32 __ctru_heap_size = 0x100000; 
pu32 __ctru_linear_heap_size = 0x40000;

PResult PHeap_Init(PHeap **heap, size_t size) {
	Result rc;
	pu32 out_addr;
	pu32 aligned_size = PALIGN_UP(size, 0x1000); // align to page

	rc = svcControlMemory(&out_addr, 0x0, 0x0, aligned_size, MEMOP_ALLOC, MEMPERM_READWRITE);
	if(R_FAILED(rc)) {
		printf("Allocation failed: 0x%08lX\n", rc);
		return PResult_Error(PERROR_ALLOC_FAIL);
	}

	*heap = (PHeap*)out_addr;
	(*heap)->size = aligned_size;
	printf("Allocated %zu bytes.\n", aligned_size);
	return PResult_Ok(NULL);
}

PResult PHeap_Deinit(PHeap **heap) {
	Result rc;
	pu32 tmp;
	pu32 heap_raw = (pu32)*heap;
	size_t heap_size = (*heap)->size;

	rc = svcControlMemory(&tmp, heap_raw, 0x0, heap_size, MEMOP_FREE, 0x0);
	if(R_FAILED(rc)) {
		printf("Failed to free memory: 0x%08lX\n", rc);
		return PResult_Error(PERROR_DEALLOC_FAIL);
	}

	*heap = NULL;
	printf("Freed %zu bytes.\n", heap_size);
	return PResult_Ok(NULL);
}
