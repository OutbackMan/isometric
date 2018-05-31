#ifndef __menu_menu_manager_h__
#define __menu_menu_manager_h__

#include <SDL2/SDL.h>

void i_menu_manager_render(SDL_Renderer* renderer);

void i_menu_manager_events(void);

void i_menu_manager_render()
{
	if (__ACTIVE_MENU.active_menu == I_MENU_MAIN) {
		i_menu_main_render();			
	} else if {
		i_menu_controls_render();		
	} else {
		return;		
	}
}

void i_menu_manager_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) {
		if (i_menu_active_get() == I_MENU_MAIN) {
			i_menu_main_events();			
		} else if {
			i_menu_controls_events();		
		} else {
			return;		
		}
	}
}

#endif
