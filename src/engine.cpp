#include "engine.hpp"

// singletons
//
static pu8 mem[PMB(1)];
static Renderer *renderer = nullptr;

PResult eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbinary_path) {
	PResult res = {};
	EResult eres{};
	PUNUSED(argc);
	PUNUSED(argv);

	MemArena *arena = nullptr;
	int *ia = nullptr;
	ERESULT_TRY(memarena_init(mem, PMB(1)), eres, printf("I FAILED!!!\n"));
	arena = ERESULT_PTR(MemArena, eres);
	printf("%p\n", arena);

	ia = (int*) memarena_alloc(arena, sizeof(int) * 5, alignof(int));
	printf("%p\n", ia);

	res = POk_int(0);
out:
	return res;
}
