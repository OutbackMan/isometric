#ifndef __restore_h__
#define __restore_h__

enum {
	UNDO_RECORD,
	REDO_RECORD
};

typedef struct {
	bool valid_undo_is_available;
	bool undo_is_available;
	bool redo_is_available;
	int undo_pos, undo_len, redo_len;
	short undo_buffer[EDITOR_RESTORE_UNDO_BUFFER_MAX];
} RestoreSystem;


#endif
