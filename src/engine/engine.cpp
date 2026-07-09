#include "engine/engine.hpp"

pi32 eentry_point(pi32 argc, const char **argv, const PMemoryLayout *memlayout, PStringView gbinary_path) {
	PUNUSED(argc);
	PUNUSED(argv);

	printf("engine entry point reached\n");

	return 0;
}
