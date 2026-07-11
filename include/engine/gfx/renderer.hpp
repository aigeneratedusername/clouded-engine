#pragma once
#include "../types.hpp"

enum class RendererError {
	idk
};

struct Renderer {
	void *backend_ctx;
};

Result<Renderer*, RendererError> renderer_init();
Result<int, RendererError> renderer_deinit();
