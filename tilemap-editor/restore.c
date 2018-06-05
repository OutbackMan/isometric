#include "restore.h"

#include <stddef.h>

#include "tilemap.h"

void editor_restore_write_undo(EditorTilemap* tilemap, int value)
{
	size_t undo_buffer_index = tilemap->undo_buffer_index;

	tilemap->undo_buffer[undo_buffer_index] = value;
	tilemap->undo_buffer_index = undo_buffer_index % EDITOR_RESTORE_UNDO_BUFFER_MAX;

}

void editor_restore_begin_undo(EditorTilemap* tilemap)
{
	editor_restore_write_undo(tilemap, EDITOR_RESTORE_UNDO_RECORD);	
	tilemap->is_undoing = true;
}


