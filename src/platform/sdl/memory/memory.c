#define PLATFORM_INTERNAL
#include "platform/memory/memory.h"
#include "platform/internal/memory.h"

#if defined(__unix__)
	#include <sys/mman.h>
#elif defined(_WIN32)
	#include <windows.h>
#endif

static PMemoryLayout memlayout;

PResult pmemory_init(const PMemoryConfig memconf) {
	PResult res = { 0 };
	size_t nentries = 0;

	for(const PMemoryConfigEntry *entry = memconf.entries; entry->region_type != PMEMORY_REGION_INVALID; entry++)
		nentries++;

	PRESULT_TRY(pialloc(sizeof(PMemoryRegion) * nentries, _Alignof(PMemoryRegion)), res, { 
		res = PErr(PERROR_ALLOC_FAIL);
		goto out; 
	});

	memlayout.regions = PRESULT_PTR(PMemoryRegion, res);
	memlayout.nregions = nentries;

	for(size_t i = 0; i < nentries; i++) {
		memlayout.regions[i].size = memconf.entries[i].region_size;
		memlayout.regions[i].type = memconf.entries[i].region_type;

		switch(memlayout.regions[i].type) {
			case PMEMORY_REGION_DEFAULT:
			case PMEMORY_REGION_CONTIGUOUS: {
				#ifdef __unix__ 
					pu8 *mem = mmap(
						NULL,
						memlayout.regions[i].size,
						PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS,
						-1,
						0
					);
					if(mem == MAP_FAILED) {
						res = PErr(PERROR_ALLOC_FAIL);
						goto out;
					}
					memlayout.regions[i].memory = mem;
				#endif
				break;
			}

			case PMEMORY_REGION_INVALID:
				break;
		}

		printf("%zu\n", memlayout.regions[i].size);
	}

	res = POk_ptr(&memlayout);
out:
	if(PFailed(res)) {
		for(size_t i = 0; i < memlayout.nregions; i++) {
			#ifdef __unix__
				munmap(memlayout.regions[i].memory, memlayout.regions[i].size);
			#endif
		}
	}

	return res;
}

PResult pmemory_deinit(const PMemoryConfig memconf) {
	PResult res = { 0 };

	for(size_t i = 0; i < memlayout.nregions; i++) {
		switch(memlayout.regions[i].type) {
			case PMEMORY_REGION_DEFAULT:
			case PMEMORY_REGION_CONTIGUOUS: {
				#ifdef __unix__
					pi32 rc = munmap(memlayout.regions[i].memory, memlayout.regions[i].size);
					if(rc != 0) {
						res = PErr(PERROR_DEALLOC_FAIL);
						goto out;
					}
				#endif
				break;
			}

			case PMEMORY_REGION_INVALID:
				break;
		}
	}

	res = POk_int(0);
out:
	return res;
}
