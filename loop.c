#include "loop.h"

#include <SDL2/SDL.h>

void i_loop__execute(
			I_Isometric* isometric, 
			float desired_fps, 
			unsigned max_update_steps, 
)
{
	const float DESIRED_FRAME_TIME_MS = 1000.0f / desired_fps;

	float total_delta_time;
	unsigned update_counter;

	while (isometric->want_to_run) {
		for (u32 prev_frame_time = SDL_GetTicks(); !isometric->want_to_run; ) {
			u32 cur_frame_time = SDL_GetTicks() - prev_frame_time;
			prev_frame_time = cur_frame_time;
			total_delta_time = cur_frame_time / DESIRED_FRAME_TIME_MS;

			

			update_counter = 0;
			while (total_delta_time > 0.0f && update_counter < max_update_steps) {
				delta_time = G_MATH_FLOAT_MIN(total_delta_time, 1.0f);
				total_delta_time -= delta_time;
				
				update();

				++update_counter;
			}
			
			draw();

		}
	}

}
