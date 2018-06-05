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
	int sprite_id;
	char* category;
} EditorTileMap__Tile;

typedef struct {
	EditorTileMap__Tile* tiles;	
	size_t num_of_tiles;
} EditorTileMap__TilePalette;

typedef struct {
	unsigned* placed_tiles;
	size_t num_placed_tiles;
	size_t current_placed_tile_index;
	float* tile_properties; // ???
	
	EditorTileMap__TilePalette* tile_palette;
	bool tileinfo_is_dirty;

	EditorTileMap__Link* tile_links;

	unsigned tile_render_width;
	unsigned background_tile_id;
	unsigned tile_render_height;

	bool valid_undo_is_available;
	bool undo_is_available;
	bool redo_is_available;
	unsigned char padding;
	int cur_palette_count;
	int palette_scroll;
	int property_mode;
	int undo_pos, undo_len, redo_len;
	short undo_buffer[EDITOR_RESTORE_UNDO_BUFFER_MAX];
} EditorTilemap;

#endif
