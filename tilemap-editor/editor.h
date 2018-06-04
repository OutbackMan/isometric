#ifndef __editor_h__
#define __editor_h__

// DRAW_RECT
// DRAW_TILE

/******************************************************************************
ACTS AS GUI/UI
******************************************************************************/

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "tilemap.h"

typedef struct {
	EDITOR_TOOL_ID active_tool_id;
	SDL_Event* active_event;
	int active_id; // ???replace with is_active???
	int hot_id; // ???
	int next_hot_id; // ???
	int event; // ???editor specific event???
	int mouse_x, mouse_y;
	int dx, dy; // ???
	int ms_time; // ???
	int shift, scroll_key;
	bool is_initted;
	int side_extended[2]; // ???
	ColourRect delay_rect[MAX_DELAY_RECT]; // ???
	int delay_count; // ???
	bool show_grid;
	bool show_links;
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
	float dt; // ???
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

#endif
