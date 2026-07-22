#include "core/platform/video/screen.h"
#include "SDL3/SDL.h"

static SDL_Window *window_handle = NULL;
static SDL_GLContext gl_ctx = NULL;
static pu32 window_width = 1280;
static pu32 window_height = 720;

PResult pscreen_init() {
	PResult res = { 0 };

	// assuming OpenGL for now. restructuring is needed later for different backends
	// but fuck it, it's been nearly a month and we still have no renderer :/
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS,
	#ifdef __APPLE__ 
		SDL_GL_CONTEXT_FORWARD_COMPATIBILE_FLAG
	#else
		0
	#endif
	);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_WindowFlags window_flags = 
		SDL_WINDOW_OPENGL 	|
		SDL_WINDOW_HIDDEN 	|
		SDL_WINDOW_RESIZABLE;

	window_handle = SDL_CreateWindow("clouded engine!", window_width, window_height, window_flags);
	if(!window_handle) {
		printf("error\n");
		res = PErr(PERROR_SCREEN_INIT_FAIL);
		goto out;
	}

	gl_ctx = SDL_GL_CreateContext(window_handle);
	if (!gl_ctx) {
		res = PErr(PERROR_SCREEN_INIT_FAIL); // TODO: add proper errors
		goto out;
	}

	SDL_GL_MakeCurrent(window_handle, gl_ctx);
	SDL_GL_SetSwapInterval(1);
	SDL_SetWindowPosition(window_handle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_ShowWindow(window_handle);

	res = POk_int(0);
out:
	return res;
}

PResult pscreen_deinit() {
	PResult res = { 0 };
	
	SDL_DestroyWindow(window_handle);
	res = POk_int(0);
out:
	return res;
}

PResult pscreen_get_size(pu32 *width, pu32 *height) {
	if (!width || !height)
		return PErr(PERROR_NULLPTR);

	*width = window_width;
	*height = window_height;
	return POk_int(0);
}

PHandle pscreen_get() {
	return (PHandle)window_handle;
}
