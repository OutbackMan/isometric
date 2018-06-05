#ifndef __events_h__
#define __events_h__

#include <SDL2/SDL.h>

void editor_events(SDL_Event* event);

typedef struct {
	int mouse_x;
	int mouse_y;
} EditorEventHolder;

#endif
