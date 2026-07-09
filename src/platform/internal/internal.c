#define PLATFORM_INTERNAL
#include "platform/internal/internal.h"
#undef PLATFORM_INTERNAL

PResult pinternal_init() {
	PResult res = { 0 };
	PRESULT_TRY(pimeminit(), res, goto out);
out:
	return res;
}

PResult pinternal_deinit() {
	PResult res = { 0 };
out:
	return res;
}
