#pragma once
#include "types.hpp"

enum EStatus {
	ESTATUS_OK,
	ESTATUS_ERROR
};

typedef uint16_t EErrorDomain;
typedef uint16_t EErrorCode;

struct EError {
	EErrorDomain 	domain;
	EErrorCode  	code;
};

struct EResult {
	EStatus status;
	union {
		uintptr_t 	value;
		EError 		error;
	};
};
