#pragma once
#include "../types.hpp"

#include "arena.hpp"

typedef PSlice MemCursor;
// a helper to grab nbytes from the front of a memory region
PSlice memtake_front(MemCursor *memory, size_t nbytes);
