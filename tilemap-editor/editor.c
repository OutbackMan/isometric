#include "editor.h"

#include "config.h"
#include "tools.h"
#include "panels.h"

Editor* editor_create(void) // stbte_init_gui()
{
	Editor* editor = xmalloc(sizeof(Editor));	

	editor->active_tool = EDITOR_TOOL_BRUSH;

	editor->want_to_show_links = true;	

	for (size_t panel_index; panel_index < EDITOR_PANELS__NUM; ++panel_index) {
		editor->panels[panel_index].is_expanded = true;
		editor->panels[panel_index].delta_height = 0;
		editor->panels[panel_index].position = POSITION_LEFT;
	}
	editor->panel[EDITOR_PANEL_TOOLBAR].position = POSITION_TOP;
	editor->panel[EDITOR_PANEL_COLORPICKER].position = POSITION_RIGHT;

	editor->left_width = 80;
	editor->right_width = 80;

	// ???init font???

	return editor;
}
