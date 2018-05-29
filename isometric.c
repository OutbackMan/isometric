#include "isometric.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>

I_Isometric* isometric_create(void)
{
	SDL_Init(SDL_VIDEO);

	I_Isometric* isometric = malloc(sizeof(I_Isometric));

	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); // debugging

	isometric->window = SDL_CreateWindow(
						"isometric", 
						SDL_WINDOWPOS_CENTERED, 
						SDL_WINDOWPOS_CENTERED,
						WINDOW_WIDTH, 
						WINDOW_HEIGHT, 
						SDL_WINDOW_RESIZABLE
					);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	isometric->renderer = SDL_CreateRenderer(
							isometric->window, 
							-1,
							SDL_RENDERER_ACCELERATED | 
							SDL_RENDERER_PRESENTVSYNC |
							SDL_RENDERER_TARGETTEXTURE
						);

	isometric->want_to_run = true;

	IMG_Init(IMG_INIT_PNG);
}	

void isometric_destroy(I_Isometric* isometric)
{
	SDL_DestroyWindow(isometric->window);	
	SDL_DestroyRenderer(isometric->renderer);	
	
	IMG_Quit();
	SDL_Quit();

	free(isometric);
}
