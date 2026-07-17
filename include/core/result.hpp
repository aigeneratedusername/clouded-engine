#pragma once
#include "platform/types.h"

enum EStatus {
	ESTATUS_OK,
	ESTATUS_ERROR
};

/*
 * NOTE: This isn't a perfect solution however, I've yet to find better
 * My biggest gripe is that a central enum for domains or a domain registry system
 * is needed. Along with that, each error domain is required to carry it's own
 * erorr codes which isn't always handled cleanly.
 */
enum EErrorDomain : uint16_t {
	EERROR_DOMAIN_MEMORY = 0,
	EERROR_DOMAIN_RENDERER,
	EERROR_DOMAIN_CONTAINERS,
	EERORR_DOMAIN_PLATFORM,
	EERROR_DOMAIN_UNAVAILABLE
};

enum EErrorCommonCode : uint16_t {
	EERROR_OUT_OF_MEMORY,
	EERROR_INVALID_PARAMS,
	EERORR_UNKNOWN
};

typedef uint16_t EErrorCode;
typedef uint32_t EError;

struct EResult {
	EStatus status;
	union {
		uintptr_t 	value;
		EError 		error;
	};
};

#define ERESULT_PTR(T, res) ((T*)(res).value)
#define ERESULT_UINT(res) 	((uintptr_t)(res).value)
#define ERESULT_INT(res) 	((intptr_t)(res).value)

/*
 *  NOTE: DO NOT USE THIS WITH NON EResult RETURN TYPES!
 *  for PResults use PRESULT_TRY, for function that return neither? 
 *  idk go fuck yourself? 
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
