#pragma once
#include "../platform/types.h"

typedef pu32 Color;

struct ColorNormal {
	pf32 r;
	pf32 g;
	pf32 b;
	pf32 a;
};

struct Vertex {
	pf32 x, y;
	pf32 uv1, uv2;
};
