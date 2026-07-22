#include "glad/glad.h"
#include "SDL3/SDL.h"
#include "core/renderer/renderer.hpp"
#include "core/renderer/types.hpp"
#include "core/memory/memory.hpp"

struct Renderer {
	pu32 screen_width;
	pu32 screen_height;
	pu32 vao; 
	pu32 vbo; 
	pu32 ebo;
	pu32 shader_program;
	ColorNormal clear_color;
};

static MemArena *perm_arena = nullptr;
static MemArena *frame_arena = nullptr;
static Renderer *renderer = nullptr;

static Vertex vertices[] = {
	{ .x = -0.5f, .y = -0.5f, .uv1 = 0.0f, .uv2 = 0.0f },
	{ .x =  0.5f, .y = -0.5f, .uv1 = 0.0f, .uv2 = 0.0f },
	{ .x =  0.0f, .y =  0.5f, .uv1 = 0.0f, .uv2 = 0.0f },
};

static const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

EResult renderer_init(PSlice memory) {
	EResult res = {};
	MemCursor memc = memory;

	PSlice perm_arena_mem = memtake_front(&memory, PMB(6));
	PSlice frame_arena_mem = memtake_front(&memory, PMB(2));
	
	ERESULT_TRY(memarena_init(perm_arena_mem.ptr, perm_arena_mem.len), res, goto out);
	perm_arena = ERESULT_PTR(MemArena, res);

	ERESULT_TRY(memarena_init(frame_arena_mem.ptr, frame_arena_mem.len), res, goto out);
	frame_arena = ERESULT_PTR(MemArena, res);

	renderer = (Renderer*) memarena_alloc(perm_arena, sizeof(Renderer), alignof(Renderer));
	if (!renderer) goto out;

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		res = EErr(EERROR_DOMAIN_RENDERER, 0x0000);
		goto out;
	}

	pscreen_get_size(&renderer->screen_width, &renderer->screen_height);
	glViewport(0, 0, renderer->screen_width, renderer->screen_height);

	renderer->clear_color = ColorNormal {
		1.0f, 1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &renderer->vao);	
	glGenBuffers(1, &renderer->vbo);
	glGenBuffers(1, &renderer->ebo);
	renderer->shader_program = glCreateProgram();

	pu32 vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertex_shader);

	pu32 fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragment_shader);

	glAttachShader(renderer->shader_program, vertex_shader);
	glAttachShader(renderer->shader_program, fragment_shader);
	glLinkProgram(renderer->shader_program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glBindVertexArray(renderer->vao);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	res = EOk_int(0);
out:
	return res;
}

EResult renderer_deinit() {
	return EOk_int(0);
}

void renderer_begin() {
	glUseProgram(renderer->shader_program);
	glBindVertexArray(renderer->vao);
}

void renderer_end() {
	glDrawArrays(GL_TRIANGLES, 0, 3);	
}

void renderer_clear() {
	glClearColor(renderer->clear_color.r, renderer->clear_color.g, renderer->clear_color.b, renderer->clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_set_clear_color(Color color) {
}

Renderer *renderer_get_ptr() {
	return renderer;
}
