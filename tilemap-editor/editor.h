#ifndef __editor_h__
#define __editor_h__

#include <SDL2/SDL.h>

#include <stdbool.h>

void editor_update(float delta_time);

void editor_render(SDL_Renderer* renderer);

// we obtain all event information from get_keyboard_state and get_mouse_state
// just call poll_events() (only check for SDL_QUIT) every frame 


#endif
