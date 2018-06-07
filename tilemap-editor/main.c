#include "editor.h"

int main(void)
{
	Editor* editor = editor_create();

	editor_events(editor, event);

	editor_update();

	editor_render();

	editor_destroy(editor);

	return 0;	
}
