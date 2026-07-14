#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef uint8_t 	pu8;
typedef uint16_t 	pu16;
typedef uint32_t 	pu32;
typedef uint64_t 	pu64;
typedef int8_t 		pi8;
typedef int16_t 	pi16;
typedef int32_t 	pi32;
typedef int64_t 	pi64;
typedef float 		pf32;
typedef double 		pf64;

typedef void* PHandle;

typedef struct {
	const pu8 	*ptr;
	size_t 		len;
} PSlice;

typedef struct {
	pu8 		*ptr;
	size_t 		len;
} PSliceMut;

typedef struct {
	const char 	*str;
	size_t 		len;
} PStringView;

typedef enum {
	PSTATUS_OK = 0,
	PSTATUS_ERR = 1,
} PStatus;

typedef enum {
	PERROR_INIT_FAIL,
	PERROR_MEMORY_INIT_FAIL,
	PERROR_SYSTEM_INIT_FAIL,
	PERROR_IO_INIT_FAIL,
	PERROR_SCREEN_INIT_FAIL,
	PERROR_AUDIO_INIT_FAIL,
	PERROR_ALLOC_FAIL,
	PERROR_DEALLOC_FAIL,
	PERROR_OUT_OF_MEMORY,
	PERROR_BAD_ALIGN,
	PERROR_INSUFFICIENT_BUF_SIZE,
	PERROR_NULLPTR,
	PERROR_INVALID_PARAMS,
	PERROR_UNDEFINED
} PError;

typedef struct {
	PStatus status;
	union {
		uintptr_t 	data;
		PError 		err;
	};
} PResult;

#ifdef __cplusplus
}
#endif
