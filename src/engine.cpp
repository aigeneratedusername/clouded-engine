#include "engine.hpp"

// singletons
static Renderer *renderer = nullptr;

PResult eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbinary_path) {
	PResult res = {};
	PUNUSED(argc);
	PUNUSED(argv);

	res = POk_int(0);

out:
	return res;
}
