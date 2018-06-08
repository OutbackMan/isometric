#include "editor.h"

#include "editor-events.h"
///////////////////////////////
// START(EVENTS)
///////////////////////////////
static inline bool ENTERED_QUIT_KEYS(const uint8_t* keyboard_state, const SDL_Keymod keyboard_modifiers)
{
	return (keyboard_state[SDL_SCANCODE_ESCAPE] != 0 || 
		((keyboard_modifiers & KMOD_LCTRL || keyboard_modifiers & KMOD_RCTRL) && keyboard_state[SDL_SCANCODE_Q]); 
}

static void editor_events_keyboard(Editor* editor)
{
	const SDL_Keymod keyboard_modifiers = SDL_GetModState();
	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

	if (ENTERED_QUIT_KEYS(keyboard_state, keyboard_modifiers)) {
		prompt_quit();
	}

	editor->input_values->shift_is_pressed = ((keymod & KMOD_LCTRL) || (keymod & KMOD_RCTRL));

	editor->input_values->scroll_key_is_pressed = (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE] != 0);
}
///////////////////////////////
// END(EVENTS)
///////////////////////////////


///////////////////////////////
// START(UPDATE)
///////////////////////////////
void editor_update(Editor* editor, float delta_time)
{
	
}
///////////////////////////////
// END(UPDATE)
///////////////////////////////


///////////////////////////////
// START(RENDER)
///////////////////////////////
void editor_render(SDL_Renderer* renderer)
{
	__SDL_RenderQuadFill(
				renderer, 
				0, 
				0, 
				window_width, 
				window_height, 
				EDITOR_CONFIG_BG_COLOUR);

	editor_tile_map_render(editor->tile_map, renderer);
}
///////////////////////////////
// END(RENDER)
///////////////////////////////
