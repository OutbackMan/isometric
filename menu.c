// SDLK_Escape;
// void toggle_menu() { if (isometric->view == GAME) isometric->view = MENU; }
// 41:00

bool asking_for_restart_confirmation = false;
int current_menu_choice;

enum {
	MENU_CHOICE_RESUME,
	MENU_CHOICE_RESTART
};

typedef struct {
	int choice_2_value;	
} MenuState;

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
	}
}

menu_advance_choice(int delta)
{
	current_menu_choice += delta;	

	if (current_menu_choice < 0) {
		current_menu_choice += MENU_NUM_CHOICES;	
	} else if (current_menu_choice > MENU_NUM_CHOICES) {
		current_menu_choice = 0;		
	}
}

draw_text(index)
{
	if (index == current_menu_choice) {
		font_colour == { 255, 255, 255, 255 };
	}
}

menu_render()
{
	int centre_x = screen_width / 2;
	int cursor_y = screen_height - menu->title_font->height * 1.7f;

	draw_text(centre_x, cursor_y, "TITLE", MENU_CHOICE_TITLE);	

	menu_render_choices();
}

menu_render_choices(centre_x, cursor_y)
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
}
