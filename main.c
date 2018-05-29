#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "isometric.h"

#define SDL_ASSERT_LEVEL 2

int main(int argc, char** argv)
{
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

	I_Isometric* isometric = i_isometric_create();

	const float DESIRED_FPS = 60.0f;
	const unsigned MAX_UPDATE_STEPS = 6;

	i_isometric_execute(isometric, DESIRED_FPS, MAX_UPDATE_STEPS);

	i_isometric_destroy(isometric);

	return EXIT_SUCCESS;	
}


