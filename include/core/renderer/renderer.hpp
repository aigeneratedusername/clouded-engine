#pragma once
#include "../types.hpp"
#include "../platform/video/video.h"

typedef struct Renderer Renderer;

EResult renderer_init(PSlice memory);
EResult renderer_deinit(Renderer *renderer);

void 	renderer_begin(Renderer &renderer);
void 	renderer_end(Renderer &renderer);
void 	renderer_clear();
void 	renderer_draw_texture(Renderer &renderer, PTexture *texture);
void 	renderer_set_clear_color(Renderer &renderer, pu32 color);
void 	renderer_set_ptr(Renderer *renderer);
