#include "editor.h"

int main(void)
{
	Editor* editor = editor_create();

	while (editor->want_to_run) {
		editor_events();
		editor_update();
		editor_render();
	}

	editor_destroy();

	return 0;	
}
