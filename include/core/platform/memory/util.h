#pragma once
#include "types.h"
#include "../util.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Converts n bytes to kilobytes */
#define PKB(n) 					((size_t)(n) << 10)
/** @brief Converts n bytes to megabytes */
#define PMB(n) 					((size_t)(n) << 20)
/** @brief Converts n bytes to gigabytes */
#define PGB(n)					((size_t)(n) << 30)

/** @brief Helper to get size of stack allocated array */
#define PARRAY_SIZE(arr) 		(sizeof((arr)) / sizeof((arr)[0]))
/** @brief Helper to zero a pointer */
#define PZERO(ptr) 				memset((ptr), 0, sizeof(*(ptr)))
/** @brief Helper to zero an array */
#define PZERO_N(ptr, n) 		memset((ptr), 0, sizeof(*(ptr)) * (n))

/** @breif Helper to get alignment of a variable or type */
#define PALIGNOF(T) 			((size_t)offsetof(struct { pu8 b; T t; }, t))

/** @brief Helper to align memory up to a value */
#define PALIGN_UP(val, align)   (((val) + (align) - 1) & ~((align) - 1))
/** @breif Helper to align memory down to a value */
#define PALIGN_DOWN(val, align) ((val) & ~((align) - 1))
/** @brief Helper to check if a value is aligned to a value */
#define PIS_ALIGNED(val, align) (((val) & ((align) - 1)) == 0)


#ifdef __cplusplus
}
#endif
