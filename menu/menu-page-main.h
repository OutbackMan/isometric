// each menu defines its own render and events
void i_menu_main_render()
{
	
}

void i_menu_main_events()
{
		
}


void i_menu_page_events(SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN) {
		switch (event->key.keysym.sym) {
		case SDLK_DOWN:
			active_option++;
			break;
		case SDLK_UP: 
			active_option--;
			break;
		case SDLK_ENTER:
			if (__MENU_MAIN.active_option == MENU_MAIN_LOAD_MENU) {
				__ACTIVE_MENU.active_menu = MENU_LOAD;			
			}
			break;
		}

		if (active_option < 0) {
			active_option = num_options;		
		} else if (active_option >= num_options) {
			active_option = 0;	
		} else {
			return;		
		}
	}	
}

