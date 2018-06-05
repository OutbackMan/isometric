#ifndef __render_h__
#define __render_h__

#include <SDL2/SDL.h>

typedef enum {
	EDITOR_RENDER_MODE_DEEMPHASISE,
	EDITOR_RENDER_MODE_NORMAL,
	EDITOR_RENDER_MODE_EMPHASISE
} EDITOR_RENDER_MODE;

void editor_render_rect(int x0, int y0, int x1, int y1, SDL_Color* color);

void editor_render_line(int x0, int y0, int x1, int y1, SDL_Color* color);



void editor_render_tile(int x0, int y0, unsigned tile_id, EDITOR_RENDER_MODE render_mode, float* tile_data);

#endif
