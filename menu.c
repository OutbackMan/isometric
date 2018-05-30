// SDLK_Escape;
// void toggle_menu() { if (isometric->view == GAME) isometric->view = MENU; }
// 41:00

Menu* menu_create()
{
	// labels
	menu->title_font = TTF_OpenFont();	
	menu->body_font = TTF_OpenFont();	
	menu->version_font = TTF_OpenFont();	
}

menu_render()
{
	int centre_x = screen_width / 2;
	int cursor_y = screen_height / 2;

	int stride = 1.7 * font->height;

	// TITLE
	draw_text(centre_x, cursor_y, "");	
	cursor_y -= stride;

	// SUB TITLE
	draw_text(body_text_x, body_text_y, "");	
	cursor_y -= stride;
	

	
	menu_render_choices();

	menu_render_version();

}

menu_render_version()
{
	
}

menu_render_choices()
{
	
}
