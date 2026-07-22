#pragma once
#include "../types.hpp"
#include "../platform/video/video.h"

typedef struct Renderer Renderer;

EResult 	renderer_init(PSlice memory);
EResult 	renderer_deinit();

void 		renderer_begin();
void 		renderer_end();
void 		renderer_clear();
void 		renderer_draw_texture(PTexture *texture);
void 		renderer_set_clear_color(pu32 color);
Renderer 	*renderer_get_ptr();
