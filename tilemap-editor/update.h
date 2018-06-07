#include "update.h"

// do_event()
static void events_process()
{
	editor->next_hot_id = 0;
	editor->hot_id = editor->next_hot_id;

	if (editor->is_active) {
		if (editor->active_event == SDL_MOUSEBUTTON_UP) {
			if (!editor->restore_system->is_pasting) {
				editor->is_active = false;
				if (editor->restore_system->is_undoing) {
					restore_end_undoing();
				}
				editor->is_scrolling = false;
				editor->is_dragging = false;

			}
		}
	}

	handle_pasting();
	handle_dragging();
}
