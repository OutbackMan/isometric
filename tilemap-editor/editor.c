#include "editor.h"

#include "config.h"
#include "tools.h"
#include "panels.h"

///////////////////////////////
// START(CONSTRUCTOR)
///////////////////////////////
Editor* editor_create(void)
{
	Editor* editor = xmalloc(sizeof(Editor));	

	return editor;
}
///////////////////////////////
// END(CONSTRUCTOR)
///////////////////////////////


///////////////////////////////
// START(DESTRUCTOR)
///////////////////////////////
void editor_destroy(Editor* editor)
{
	free(editor);	
}
///////////////////////////////
// END(DESTRUCTOR)
///////////////////////////////


///////////////////////////////
// START(EVENTS)
///////////////////////////////
void editor_events(Editor* editor, SDL_Event* event)
{
	events_keyboard(editor);

	switch (event->type) {
	case SDL_QUIT:
		game->want_to_run = false;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		events_update_mouse_position(editor, event->motion.x, event->motion.y);	
		break;
	default:
		break;
	}
}

static inline bool ENTERED_QUIT_KEYS(const uint8_t* keyboard_state, const SDL_Keymod keyboard_modifiers)
{
	return (keyboard_state[SDL_SCANCODE_ESCAPE] != 0 || 
		((keyboard_modifiers & KMOD_LCTRL || keyboard_modifiers & KMOD_RCTRL) && keyboard_state[SDL_SCANCODE_Q]); 
}

static void events_keyboard(Editor* editor)
{
	const SDL_Keymod keyboard_modifiers = SDL_GetModState();

	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

	if (ENTERED_QUIT_KEYS(keyboard_state, keyboard_modifiers)) {
		prompt_quit();
	}

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
///////////////////////////////
// END(EVENTS)
///////////////////////////////


///////////////////////////////
// START(UPDATE)
///////////////////////////////
void editor_update(Editor* editor, float delta_time);


///////////////////////////////
// END(UPDATE)
///////////////////////////////

///////////////////////////////
// START(RENDER)
///////////////////////////////
void editor_render(Editor* editor, SDL_Renderer* renderer);


///////////////////////////////
// END(RENDER)
///////////////////////////////
