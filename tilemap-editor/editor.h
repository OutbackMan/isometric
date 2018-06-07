#ifndef __editor_h__
#define __editor_h__

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "tilemap.h"

typedef struct {
			
} Editor__InputValues;

typedef struct {
	EDITOR_TOOL_ID active_tool_id;
	Editor__InputValues* input_values;
	bool want_to_run;
	int active_id; // ???replace with is_active???
	int dx, dy; // ???
	int shift, scroll_key;
	int side_extended[2]; // ???
	bool show_grid;
	int brush_state;
	int eyedrop_x, eyedrop_y, eyedrop_last_layer; // ???move into own???
	int pasting, paste_x, paste_y;
	int scrolling, start_x, start_y;
	int last_mouse_x, last_mouse_y;
	int accum_x, accum_y;
	int linking;
	int dragging;
	int drag_x, drag_y, draw_w, drag_h;
	int drag_offx, drag_offy, drag_dest_x, drag_dest_y;
	int undoing;
	int has_selection, select_x0, select_x1, select_y0, select_y1;
	int sx, sy; // ???
	int x0, x1, y0, y1, left_width, right_width;
	float alert_timer; // ???
	const char* alert_msg;
	Panel panels[NUM_PANELS];
	short copy_buffer[MAX_COPY][MAX_LAYERS];
	float copy_props[MAX_PROPS][MAX_PROPERTIES];
	Link copy_links[MAX_COPY];
	int copy_src_x, copy_src_y;
	TileMap* tilemap;
	int copy_width, copy_height, has_copy, copy_has_props;
} Editor;

Editor* editor_create(void);

void editor_destroy(Editor* editor);

void editor_events(Editor* editor, SDL_Event* event);

void editor_update(Editor* editor, float delta_time);

void editor_render(Editor* editor, SDL_Renderer* renderer);

#endif
