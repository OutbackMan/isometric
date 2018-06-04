#include "editor.h"

Editor* editor_create(void)
{
	Editor* editor = xmalloc(sizeof(Editor));	

	editor->active_tool_id = EDITOR_TOOL_ID_BRUSH;
	editor->active_event = NULL;

	editor->want_to_show_links = true;	

	for (size_t panel_index; panel_index < NUM_PANELS; ++panel_index) {
		editor->panel[panel_index].is_expanded = true;
		editor->panel[panel_index].delta_height = 0;
		editor->panel[panel_index].side = SIDE_LEFT;
	}

	editor->panel[PANEL_TOOLBAR] = SIDE_TOP;
	editor->left_width = 80;
	editor->right_width = 80;
}
