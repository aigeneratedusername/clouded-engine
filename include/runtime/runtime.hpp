#pragma once
#include "../core/types.hpp"
#include "../core/result.hpp"

EResult runtime_init(PSlice memory);
EResult runtime_deinit();
EResult runtime_mainloop();
