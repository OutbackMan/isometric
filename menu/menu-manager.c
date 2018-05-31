#include "menu-manager.h"

#include <SDL2/SDL.h>

#include "menu-active-page.h"

void i_menu_manager_events(void)
{
	switch (i_menu_active_page_get()) {
	case MENU_MAIN:
		i_menu_main_events();
		break;
	case MENU_CONTROLS:
		i_menu_controls_events();
		break;
	default:
		break;
	}	
}

void i_menu_manager_render(SDL_Renderer* renderer)
{
	switch (i_menu_active_page_get()) {
	case MENU_MAIN:
		i_menu_main_render();
		break;
	case MENU_CONTROLS:
		i_menu_controls_render();
		break;
	default:
		break;
	}	
	
}


void i_menu_manager_update(float delta_time)
{
	switch (i_menu_active_page_get()) {
	case MENU_MAIN:
		i_menu_main_update();
		break;
	case MENU_CONTROLS:
		i_menu_controls_update();
		break;
	default:
		break;
	}	
}
