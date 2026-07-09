#include "platform/util.h"

// --------------------------------------
// Results
// --------------------------------------

PResult POk_ptr(void *ptr) {
	return (PResult) {
		.status = PSTATUS_OK, 
		.data = (uintptr_t)ptr
	};
}

PResult POk_uint(uintptr_t val) {
	return (PResult) {
		.status = PSTATUS_OK,
		.data = val
	};
}

PResult POk_int(intptr_t val) {
	return (PResult) {
		.status = PSTATUS_OK,
		.data = (uintptr_t)val
	};
}

PResult PErr(PError err) {
	return (PResult) {
		.status = PSTATUS_ERR,
		.err = err
	};
}

bool PFailed(PResult res) {
	return res.status != PSTATUS_OK;
}

const char* PStatusToStr(PStatus status) {
	return NULL;
}

// --------------------------------------
// Strings
// --------------------------------------
PStringView pstring_view_init(const char *str) {
	return (PStringView) {
		.str = str,
		.len = strlen(str)
	};
}
