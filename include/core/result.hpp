#pragma once
#include "types.hpp"

enum EStatus {
	ESTATUS_OK,
	ESTATUS_ERROR
};

typedef uint16_t EErrorDomain;
typedef uint16_t EErrorCode;
typedef uint32_t EError;

struct EResult {
	EStatus status;
	union {
		uintptr_t 	value;
		EError 		error;
	};
};

#define ERESULT_PTR(T, res) ((T*)(res).data)
#define ERESULT_UINT(res) 	((uintptr_t)(res).data)
#define ERESULT_INT(res) 	((intptr_t)(res).data)

/*
 *  NOTE: DO NOT USE THIS WITH NON EResult RETURN TYPES!
 * for PResults use PRESULT_TRY, for function that return neither? 
 * idk go fuck yourself? 
 */
#define ERESULT_TRY(expr, res, ...)		\
	do { 								\
		(res) = (expr); 				\
		if(EFailed((res))) {			\
			__VA_ARGS__;				\
		} 								\
	} while(0) 							\

static inline EResult EErr(EErrorDomain domain, EErrorCode code) {
	return {
		.status = ESTATUS_ERROR,
		.error = ((uint32_t) domain << 16) | (uint32_t) code
	};
}

static inline EResult EOk_ptr(void *ptr) {
	return {
		.status = ESTATUS_OK,
		.value = (uintptr_t) ptr
	};
}

static inline EResult EOk_int(intptr_t val) {
	return {
		.status = ESTATUS_OK,
		.value = (uintptr_t) val
	};
}

static inline EResult EOk_uint(uintptr_t val) {
	return {
		.status = ESTATUS_OK,
		.value = val
	};
}

static inline bool EFailed(EResult res) {
	return res.status != ESTATUS_OK;
}
