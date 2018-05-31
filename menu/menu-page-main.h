typedef enum {
	MENU_MAIN_RESUME,
	MENU_MAIN_QUIT
} MENU_MAIN_OPTION_ID;

static struct {
	MENU_MAIN_OPTION_ID active_option;	
	int num_options;
	bool asking_for_quit_confirmation;
} __MENU_MAIN;

#define ACTIVE_TEXTURE_NAME(option, name) \
	((__MAIN_MENU.active_option == option) ? (name ## _active) : (name))

void i_menu_main_render()
{
	// draw bg

	// draw title		
		
	menu_main_render_option(MENU_MAIN_RESUME, texture_map["main_menu_resume_option"]);
}

static void menu_main_render_option(MENU_MAIN_OPTION_ID option_id, SDL_Texture* font_texture)
{
	if (current_option == __MAIN_MENU.active_option) {
		SDL_RenderCopy(renderer, font_texture
	}
}

void i_menu_page_events(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event->type == SDL_KEYDOWN) {
			switch (event->key.keysym.sym) {
			case SDLK_DOWN:
				active_option++;
				break;
			case SDLK_UP: 
				active_option--;
				break;
			case SDLK_ENTER:
				menu_main_handle_enter();
				break;
			}
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

static void menu_main_handle_enter(void)
{
	if (__MENU_MAIN.active_option == MENU_MAIN_RESUME) {
		isometric->view = GAME;	
	} else if (__MENU_MAIN.active_option == MENU_MAIN_QUIT) {
		if (__MENU_MAIN.asking_for_quit_confirmation) {
			exit(0);			
		} else {
			__MENU_MAIN.asking_for_quit_confirmation = true;		
		}
	}
	
}

