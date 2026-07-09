#include "platform/display/screen.h"
#include "SDL3/SDL.h"

static SDL_Window *window_handle = NULL;
static pu32 window_width = 1280;
static pu32 window_height = 720;

PResult pscreen_init() {
	PResult res = { 0 };

	SDL_WindowFlags window_flags = 
		SDL_WINDOW_OPENGL 	| 
		SDL_WINDOW_RESIZABLE;

	window_handle = SDL_CreateWindow("clouded engine!", window_width, window_height, window_flags);
	if(!window_handle) {
		res = PErr(PERROR_SCREEN_INIT_FAIL);
		goto out;
	}

	SDL_SetWindowPosition(window_handle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

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
