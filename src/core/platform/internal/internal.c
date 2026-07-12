#define PLATFORM_INTERNAL
#include "core/platform/internal/internal.h"

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
