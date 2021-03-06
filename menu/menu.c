/*
void handle_escape()
{
	if (isometric->view == GAME) {
		isometric->view = MENU;
		isometric->menu_manager->current_menu_page = &main;
	} else if (menu_manager->current_page == LOAD) {
		menu_manager->current_page = MAIN;		
	} else {
		isometric->view = GAME;
		isometric->menu_manager->current_menu_page = NULL;
	}
}
	if (event.keysym.sym == SDLK_ESCAPE) {
	}
*/
// void toggle_menu() { if (isometric->view == GAME) isometric->view = MENU; }

bool asking_for_restart_confirmation = false;
int current_menu_choice;
int time_of_quit_confirmation;

enum {
	MENU_INDEX_RESUME,
	MENU_INDEX_RESTART
};

typedef struct {
	int current_option;
	int num_options;
} MenuPage;

MenuPage* main;
MenuPage* load;
MenuPage* current_menu_page;

Menu* menu_create()
{
	// labels
	menu->title_font = TTF_OpenFont();	
	menu->body_font = TTF_OpenFont();	
	menu->version_font = TTF_OpenFont();
}

menu_events()
{
	if (event.keysym.sym == SDLK_DOWN) {
		menu_advance_choice(DOWN);		
	} else if (event.keysym.sym == SDLK_UP) {
		menu_advance_choice(UP);		
	} else if (event.keysym.sym == SDLK_ENTER) {
		switch (current_menu_choice) {
		case MENU_QUIT:
			if (asking_for_quit_confirmation) {
				exit(0);
			} else {
				asking_for_quit_confirmation = true;		
			}
			break;
		case MENU_RESUME;
			isometric->view_id = ISOMETRIC;
			break;
		case MENU_LOAD:
			switch_to_menu(load);
		}		
	}
}

draw_text()
{
	if (index == current_menu_choice) {
		font_colour = { 0xff, 0x3e, 0x22, 0xff };

		white = { 0xff, 0xff, 0xff, 0xff };

		interpolation_factor = cos(SDL_GetTicks() * 2); // strobe (2 affects speed)
		interpolation_factor *= interpolation_factor; // have positive
		base = .4;
		range = .6;
		// when apply maths to form a fade out pattern, consider the graph shape that is made
		interpolation_factor = base + range * interpolation_factor;

		bg_font_colour = lerp(font_colour, white, interpolation_factor);

		bg_font_offset = menu->choice_font->height / 40;

		menu_index_resume = draw_font(+offset, -offset, bg_font_colour);
	}
}

menu_render()
{
	int centre_x = screen_width / 2;
	int cursor_y = screen_height - menu->title_font->height * 1.7f;

	draw_text(centre_x, cursor_y, "TITLE", MENU_CHOICE_TITLE);	

	menu_render_page(menu->current_page);
}

menu_render_page(current_page, centre_x, cursor_y)
{
	int stride = 1.7f * menu->choices_font->height;
	cursor_y -= stride;

	draw_text(centre_x, cursor_y, "CHOICE 1");
	cursor_y -= stride;
	
	const char* choice2_string = (asking_for_restart_confirmation ? "are you sure?" : "choice 2");
	draw_text(centre_x, cursor_y, choice2_string);
	cursor_y -= stride;

	draw_text(centre_x, cursor_y, "CHOICE 3");
	cursor_y -= stride;

	draw_text(centre_x, cursor_y, "CHOICE 4");
	cursor_y -= stride;

	// when move off a confirmation, reset text message
	if (current_menu_page->current_menu_choice != MENU_QUIT) {
		asking_for_quit_confirmation = false;	
	}
}

