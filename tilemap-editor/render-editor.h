#ifndef __draw_h__
#define __draw_h__

#include <SDL2/SDL.h>

typedef enum {
	EDITOR_DRAW_MODE_DEEMPHASISE,
	EDITOR_DRAW_MODE_NORMAL,
	EDITOR_DRAW_MODE_EMPHASISE
} EDITOR_DRAW_MODE;

void editor_draw_rect(int x0, int y0, int x1, int y1, SDL_Color* color);

void editor_draw_tile(int x0, int y0, unsigned tile_id, EDITOR_DRAW_MODE draw_mode, float* tile_data);

#endif
