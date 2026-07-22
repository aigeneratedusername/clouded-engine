#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "core/renderer/renderer.hpp"
#include "core/memory/memory.hpp"

static pf32 clear_color[4];

EResult renderer_init(PSlice memory) {
	EResult res = {};
	MemCursor memc = memory;

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		res = EErr(EERROR_DOMAIN_RENDERER, 0x0000);
	}

	pu32 screen_width, screen_height;
	pscreen_get_size(&screen_width, &screen_height);

	glViewport(0, 0, screen_width, screen_height);
out:
	return res;
}

void renderer_clear() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_set_clear_color(pu32 color) {
}
