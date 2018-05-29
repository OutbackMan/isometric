#include "draw.h"

#include <SDL2/SDL.h>

void i_draw__execute(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x3D, 0x3D, 0x3D, 0x00);	
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

