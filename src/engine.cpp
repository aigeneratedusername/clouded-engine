#include "engine.hpp"

// singletons

// memory partitions
PSlice renderer_mem;
PSlice runtime_mem; 

PResult eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbinary_path) {
	PResult res = {};
	EResult eres{};
	
	// TODO: label memory region array indexes
	runtime_mem = { memlayout->regions[0].memory + PMB(8), PMB(8) };
	renderer_mem = { memlayout->regions[1].memory + PMB(8), PMB(8) };

	ERESULT_TRY(renderer_init(renderer_mem), eres, goto out);

	ERESULT_TRY(runtime_init(runtime_mem), eres, {
		printf("Runtime initialization failed\n");
		goto out;
	});

	ERESULT_TRY(runtime_mainloop(), eres, goto out);

	res = POk_int(0);
out:
	return res;
}
