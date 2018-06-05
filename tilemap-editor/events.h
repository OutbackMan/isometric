#ifndef __events_h__
#define __events_h__

typedef enum {
	
} EDITOR_EVENT;

void editor_events(Editor* editor, SDL_Event* event, float xs, float ys, int xo, int yo)
{
	SDL_Keymod keymod = SDL_GetModState();
	bool shift_is_pressed = ((keymod & KMOD_LCTRL) || (keymod & KMOD_RCTRL));
	bool scroll_key_is_pressed = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE] != 0);

	switch (event->type) {
	case SDL_MOUSEMOTION:
		events_mouse_move(editor, (int)(xs * event->motion.x + xo), (int)(ys * event->motion.y + yo), shift_is_pressed, scroll_key_is_pressed);
		break;
	case SDL_MOUSEBUTTONUP:
		events_mouse_button();
		break;
	case SDL_MOUSEBUTTONDOWN:
		events_mouse_button();
		break;
	case SDL_MOUSEWHEEL:
		events_mouse_wheel();
		break;
	}
}

static void events_mouse_move(Editor* editor, int x, int y, bool shifted, bool scrolling)
{
	set_event(MOUSEMOVE, x, y);	
	editor->input_values->shift_is_pressed = shift_is_pressed;
	editor->input_values->scroll_key_is_pressed = scroll_key_is_pressed; 
	do_event(tilemap);
}

static void set_event(Editor* editor, EDITOR_EVENT event)
{
	editor->active_event = event;	
	editor->input_values->mouse_x = mouse_x;
	editor->input_values->mouse_y = mouse_y;
	editor->input_values->mouse_x_delta = mouse_x - editor->input_values->mouse_x_last;
	editor->input_values->mouse_y_delta = mouse_y - editor->input_values->mouse_y_last;
	editor->input_values->mouse_x_last = mouse_x;
	editor->input_values->mouse_y_last = mouse_y;
}

static void do_event()
{
	editor->next_hot_id = 0;
	editor_traverse();	
	editor->hot_id = editor->next_hot_id;
	// ...
}

static void editor_traverse()
{
	prepare_tileinfo();	
	// ...
}

static void prepare_tileinfo()
{
	if (tilemap->tileinfo_is_dirty) {
		compute_tileinfo();		
	}	
}

static void compute_tileinfo()
{
	for (size_t tile_count = 0; tile_count < tilemap->num_tiles; ++tile_count) {
		TileInfo tile_info = tilemap->tiles[tile_count]; 	
		for (size_t category_count = 0; category_count < tilemap->max_categories; ++category_count) {
			if (strcmp(tile_info->category, tilemap->categories[category_count]) {
						
			}
		}
	}	
}


#endif




