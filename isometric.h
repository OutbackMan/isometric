#ifndef __isometric_h__
#define __isometric_h__

#include <SDL2/SDL.h>

#include <stdbool.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 700

typedef struct {
	bool want_to_run;
	SDL_Window* window;	
	SDL_Renderer* renderer;	
	SDL_Event event;
} I_Isometric;


I_Isometric* i_isometric_create(void);

void i_isometric_destroy(I_Isometric* isometric);

void i_isometric_execute(
		I_Isometric* isometric, 
		float desired_fps, 
		unsigned max_update_steps
);

#endif
