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
		events_mouse_motion(editor, (int)(xs * event->motion.x + xo), (int)(ys * event->motion.y + yo), shift_is_pressed, scroll_key_is_pressed);
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

static void events_mouse_motion(Editor* editor, int mouse_x, int mouse_y, bool shifted, bool scrolling)
{
	editor->active_event = MOUSEMOVE;

	update_mouse_position(editor, mouse_x, mouse_y);	

	editor->input_values->shift_is_pressed = shift_is_pressed;
	editor->input_values->scroll_key_is_pressed = scroll_key_is_pressed; 

	events_process(tile_map);
}

static void update_mouse_position(Editor* editor, int mouse_x, int mouse_y)
{
	editor->input_values->mouse_x = mouse_x;
	editor->input_values->mouse_y = mouse_y;
	editor->input_values->mouse_x_delta = mouse_x - editor->input_values->mouse_x_last;
	editor->input_values->mouse_y_delta = mouse_y - editor->input_values->mouse_y_last;
	editor->input_values->mouse_x_last = mouse_x;
	editor->input_values->mouse_y_last = mouse_y;
}


// probably be in editor_update()
static void events_process()
{
	editor->next_hot_id = 0;
	editor_traverse(editor);	
	editor->hot_id = editor->next_hot_id;

	
}

static void editor_traverse()
{

	draw_editor_background();

	draw_tilemap();

	draw_panels();
}

void draw_tilemap()
{
	draw_background();	
	draw_tiles();
	draw_grid();
	draw_selection_border();
}

void draw_panels()
{
	compute_panel_locations(editor);

	draw_panel_bodies();
	draw_panel_selectors();
	draw_panel_expanders();

}

#endif




