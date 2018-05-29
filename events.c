#include "events.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "isometric.h"

static void events_handle_quit(I_Isometric* isometric)
{
	isometric->want_to_run = false;	
}

static void events_handle_window(I_Isometric* isometric, SDL_WindowEvent* window_event)
{
	return;
}

#define QUIT_KEYS_ARE_DOWN(keyboard_event) \
	((keyboard_event->keysym.mod == KMOD_CTRL \
	&& keyboard_event->keysym.sym == SDLK_q) \
	|| keyboard_event->keysym.sym == SDLK_ESCAPE)
static void events_handle_key_down(I_Isometric* isometric, SDL_KeyboardEvent* keyboard_event)
{
	if (QUIT_KEYS_ARE_DOWN(keyboard_event)) {
		isometric->want_to_run = false;
	} else {
		return;		
	}
}
#undef QUIT_KEYS_ARE_DOWN

static void events_handle_key_up(I_Isometric* isometric, SDL_KeyboardEvent* keyboard_event)
{
	return;
}

static void events_handle_mouse_down(I_Isometric* isometric, SDL_MouseButtonEvent* mouse_button_event)
{
	return;
}

static void events_handle_mouse_up(I_Isometric* isometric, SDL_MouseButtonEvent* mouse_button_event)
{
	return;
}

static void events_handle_mouse_motion(I_Isometric* isometric, SDL_MouseMotionEvent* mouse_motion_event)
{
	return;
}

void i_events__execute(I_Isometric* isometric)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			events_handle_quit(isometric);
			break;
		case SDL_WINDOWEVENT:
			events_handle_window(isometric, &event.window);
			break;
		case SDL_KEYDOWN:
			events_handle_key_down(isometric, &event.key);
			break;
		case SDL_KEYUP:
			events_handle_key_up(isometric, &event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			events_handle_mouse_down(isometric, &event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			events_handle_mouse_up(isometric, &event.button);
			break;
		case SDL_MOUSEMOTION:
			events_handle_mouse_motion(isometric, &event.motion);
			break;
		}
	}
}

