#pragma once
#include "../types.hpp"
#include "backend.hpp"

enum class RendererError {
	idk
};

struct Renderer {
	RenderBackend *backend;
};

Result<Renderer*, RendererError> renderer_init();
Result<int, RendererError> renderer_deinit();
