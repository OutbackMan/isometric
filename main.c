#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "isometric.h"

int main(int argc, char** argv)
{
	const float DESIRED_FPS = 60.0f;
	const unsigned MAX_UPDATE_STEPS = 6;

	I_Isometric* isometric = i_isometric_create();

	i_loop_execute(isometric, DESIRED_FPS, MAX_UPDATE_STEPS);

	i_isometric_destroy(isometric);

	return EXIT_SUCCESS;	
}
