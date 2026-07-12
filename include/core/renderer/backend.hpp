#pragma once
#include "../types.hpp"

enum class BackendError {
	InitFail,
	DeinitFail
};

typedef Result<void, BackendError> (*rendback_initfn)(void);
typedef Result<void, BackendError> (*rendback_deinitfn)(void); 

struct RenderBackend {
	rendback_initfn 	init;
	rendback_deinitfn 	deinit;
};
