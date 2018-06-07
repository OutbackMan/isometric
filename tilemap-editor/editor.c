#include "editor.h"

#include "config.h"
#include "tools.h"
#include "panels.h"

Editor* editor_create(void) // stbte_init_gui()
{
	Editor* editor = xmalloc(sizeof(Editor));	

	editor->tile_map = tilemap_create();

	editor->want_to_run = true;

	return editor;
}
