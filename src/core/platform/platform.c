#include "core/platform/platform.h"

#define PLATFORM_INTERNAL
#include "core/platform/internal/internal.h"
#undef PLATFORM_INTERNAL

PResult pinit() {
	PResult res = { 0 };

	PRESULT_TRY(pinternal_init(), res, goto out);
out:
	return res;
}

PResult pdeinit() {
	PResult res = { 0 };

	PRESULT_TRY(pinternal_deinit(), res, goto out);
out:
	return res;
}
