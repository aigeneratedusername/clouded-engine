#include "platform/system/system.h"
#include "SDL3/SDL.h"

PResult psystem_init() {
	PResult res = { 0 };

	SDL_InitFlags init_flags = 
		SDL_INIT_EVENTS | 
		SDL_INIT_AUDIO 	| 
		SDL_INIT_VIDEO 	| 
		SDL_INIT_GAMEPAD;

	if(!SDL_Init(init_flags)) {
		res = PErr(PERROR_SYSTEM_INIT_FAIL);
		goto out;
	}

	res = POk_int(0);
out:
	return res;
}

PResult psystem_deinit() {
	PResult res = { 0 };

	SDL_Quit();
	res = POk_int(0);
out:
	return res;
}
