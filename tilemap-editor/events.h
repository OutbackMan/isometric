#ifndef __events_h__
#define __events_h__

void editor_events(Editor* editor, SDL_Event* event)
{
	events_keyboard(editor);

	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		editor->active_event = event->type;
		events_update_mouse_position(editor, event->motion.x, event->motion.y);	
		break;
	default:
		break;
	}
}

static void events_keyboard(Editor* editor)
{
	SDL_Keymod keymod = SDL_GetModState();

	editor->input_values->shift_is_pressed = ((keymod & KMOD_LCTRL) || (keymod & KMOD_RCTRL));

	editor->input_values->scroll_key_is_pressed = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE] != 0);
}

static void events_update_mouse_position(Editor* editor, int mouse_x, int mouse_y)
{
	editor->input_values->mouse_x = mouse_x;
	editor->input_values->mouse_y = mouse_y;
	editor->input_values->mouse_x_delta = mouse_x - editor->input_values->mouse_x_last;
	editor->input_values->mouse_y_delta = mouse_y - editor->input_values->mouse_y_last;
	editor->input_values->mouse_x_last = mouse_x;
	editor->input_values->mouse_y_last = mouse_y;
}

#endif




