#include "editor.h"

#include "info.h"
#include "tools.h"
#include "panels.h"

Editor* editor_create(void)
{
	Editor* editor = xmalloc(sizeof(Editor));	

	editor->active_tool = EDITOR_TOOL_BRUSH;
	editor->active_event = NULL;

	editor->want_to_show_links = true;	

	for (size_t panel_index; panel_index < EDITOR_PANELS__NUM; ++panel_index) {
		editor->panel[panel_index].is_expanded = true;
		editor->panel[panel_index].delta_height = 0;
		editor->panel[panel_index].side = SIDE_LEFT;
	}
	editor->panel[PANEL_TOOLBAR] = SIDE_TOP;
	editor->panel[PANEL_COLORPICKER] = SIDE_RIGHT;

	editor->left_width = 80;
	editor->right_width = 80;

	// ???init font???
}
