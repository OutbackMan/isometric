#include "isometric.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "draw.h"
#include "update.h"
#include "events.h"

I_Isometric* i_isometric_create(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to initialise SDL2 %s", 
			SDL_GetError()
		);
		exit(EXIT_FAILURE);
	}
	
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to initialise SDL2 Image %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	I_Isometric* isometric = i_common_xmalloc(sizeof(I_Isometric));

	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1"); // debugging

	isometric->window = SDL_CreateWindow(
						"isometric", 
						SDL_WINDOWPOS_CENTERED, 
						SDL_WINDOWPOS_CENTERED,
						WINDOW_WIDTH, 
						WINDOW_HEIGHT, 
						SDL_WINDOW_RESIZABLE
					);

	if (isometric->window == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to create SDL2 window %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	isometric->renderer = SDL_CreateRenderer(
							isometric->window, 
							-1,
							SDL_RENDERER_ACCELERATED | 
							SDL_RENDERER_PRESENTVSYNC |
							SDL_RENDERER_TARGETTEXTURE
						);

	if (isometric->renderer == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to create SDL2 renderer %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	isometric->want_to_run = true;

}	

void i_isometric_destroy(I_Isometric* isometric)
{
	SDL_DestroyWindow(isometric->window);	
	SDL_DestroyRenderer(isometric->renderer);	
	
	IMG_Quit();
	SDL_Quit();

	free(isometric);
}

void i_isometric_execute(
			I_Isometric* isometric, 
			float desired_fps, 
			unsigned max_update_steps
)
{
	SDL_assert(isometric != NULL);

	const float DESIRED_FRAME_TIME_MS = 1000.0f / desired_fps;

	float total_delta_time;
	float delta_time;
	unsigned update_counter;
	uint32_t prev_frame_time = SDL_GetTicks();
	uint32_t cur_frame_time;

	while (isometric->want_to_run) {
		cur_frame_time = SDL_GetTicks() - prev_frame_time;
		prev_frame_time = cur_frame_time;
		total_delta_time = cur_frame_time / DESIRED_FRAME_TIME_MS;

		i_events__execute(isometric);

		update_counter = 0;
		while (total_delta_time > 0.0f && update_counter < max_update_steps) {
			i_update__execute();

			delta_time = I_COMMON_MIN(total_delta_time, 1.0);
			total_delta_time -= delta_time;

			++update_counter;
		}

		i_draw__execute(isometric->renderer);
	}
}
