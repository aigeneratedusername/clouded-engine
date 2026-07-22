#include "runtime/runtime.hpp"
#include "core/memory/memory.hpp"
#include "core/renderer/renderer.hpp"

#include "core/platform/video/screen.h"
#include "SDL3/SDL.h"

// singletons
static MemArena *perm_arena = nullptr;
static MemArena *scene_arena = nullptr;
static MemArena *frame_arena = nullptr;

static bool is_running = false;

EResult runtime_init(PSlice memory) {
	EResult res = {};
	MemCursor memc = memory;

	ERESULT_TRY(memarena_init(memtake_front(&memc, PMB(2)).ptr, PMB(2)), res, goto out);
	perm_arena = ERESULT_PTR(MemArena, res);
	ERESULT_TRY(memarena_init(memtake_front(&memc, PMB(5)).ptr, PMB(5)), res, goto out);
	scene_arena = ERESULT_PTR(MemArena, res);
	ERESULT_TRY(memarena_init(memtake_front(&memc, PMB(1)).ptr, PMB(1)), res, goto out);
	frame_arena = ERESULT_PTR(MemArena, res);

	is_running = true;
	res = EOk_int(0);
out:
	return res;
}

EResult runtime_deinit() {
	EResult res = {};
	return res;
}

EResult runtime_mainloop() {
	EResult res = {};

	while(is_running) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE))
				is_running = false;
		}

		renderer_clear();

		SDL_GL_SwapWindow((SDL_Window*) pscreen_get());
	}

	return res;
}
