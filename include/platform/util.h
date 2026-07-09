#pragma once
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------
// MISC Helpers
// --------------------------------------
#define PUNUSED(x) ((void)(x))

// --------------------------------------
// Results
// --------------------------------------

// presult stores a status enum and union with const void* and PErrr err.
#define PRESULT_PTR(T, res) ((T*)(res).data)
#define PRESULT_UINT(res) 	((uintptr_t)(res).data)
#define PRESULT_INT(res) 	((intptr_t)(res).data)

// ONLY TO BE USED WITH PRESULTS!!
// some of the finest macro jank i've ever written
#define PRESULT_TRY(expr, res, ...)		\
	do { 								\
		(res) = (expr); 				\
		if(PFailed((res))) {			\
			__VA_ARGS__;				\
		} 								\
	} while(0) 							\

PResult POk_ptr(void *ptr);
PResult POk_uint(uintptr_t val);
PResult POk_int(intptr_t val); 
PResult PErr(PError err);
bool 	PFailed(PResult res);

// --------------------------------------
// Strings
// --------------------------------------

const char* pstatus_tostr(PStatus status);

PStringView pstring_view_init(const char *str);


#ifdef __cplusplus
}
#endif
