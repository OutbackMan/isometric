#ifndef __tilemap_h__
#define __tilemap_h__

#include "restore.h"

enum {
	EDITOR_TILEMAP_COLOR_BACKGROUND,
	EDITOR_TILEMAP_COLOR_BORDER,         
	EDITOR_TILEMAP_COLOR_HIGHLIGHT,
	EDITOR_TILEMAP_COLOR_GRID,               
	EDITOR_TILEMAP_COLOR_SELECTION_OUTLINE1,
	EDITOR_TILEMAP_COLOR_SELECTION_OUTLINE2,
	EDITOR_TILEMAP_COLOR_TILEPALETTE_OUTLINE,
	EDITOR_TILEMAP_COLOR_TILEPALETTE_BACKGROUND,

	EDITOR_TILEMAP_COLOUR__NUM,
};

typedef enum {
	TILE_PROPERTY_NONE,
	TILE_PROPERTY_INT,
	TILE_PROPERTY_FLOAT,
	TILE_PROPERTY_BOOL,
	TILE_PROPERTY_DISABLED
} EDITOR_TILEMAP__TILE_PROPERTY;

typedef struct {
	int x;
	int y;
} EditorTilemap__Link;

typedef struct {
	int id;
	unsigned category_id;
	char* category;
} EditorTilemap__TileInfo;

extern static const EDITOR_TILEMAP_MAX_HEIGHT;

typedef struct {
	int tile_data[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH];
	float tile_properties[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH][EDITOR_PROPERTIES_MAX];
	Tilemap__Link tile_links[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH];
	unsigned tile_render_width;
	unsigned tile_render_height;
	int current_category, current_tile;
	const char* categories[EDITOR_CATEGORIES_MAX];
	int num_categories, category_scroll;
	Tilemap__TileInfo* tiles;
	int num_tiles, max_tiles, digits;
	bool valid_undo_is_available;
	bool undo_is_available;
	bool redo_is_available;
	unsigned char padding;
	int cur_palette_count;
	int palette_scroll;
	bool tileinfo_is_dirty;
	int property_mode;
	int undo_pos, undo_len, redo_len;
	short background_tile;
	unsigned char id_in_use[32768 >> 3];
	short undo_buffer[EDITOR_RESTORE_UNDO_BUFFER_MAX];
} EditorTilemap;

#endif
