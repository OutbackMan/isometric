#ifndef __tilemap_h__
#define __tilemap_h__

#include "restore.h"
#include "sprite-sheet.h"

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

#define MAX_TILES_X 2000
#define MAX_TILES_Y 2000

typedef struct {
	sprite_id_t tiles[MAX_TILES_X * MAX_TILES_Y];
	size_t num_tiles_x; // max_x
	size_t num_tiles_y;
	size_t current_placed_tile_index;
	
	SpriteSheet* tile_palette;
	int cur_palette_count;
	int palette_scroll;

	unsigned tile_render_width;
	unsigned tile_render_height;

	RestoreSystem* restore_system;
} EditorTileMap;


EditorTileMap* editor_tile_map_create(void);

void editor_tile_map_destroy(EditorTileMap* editor);

void editor_tile_map_events(EditorTileMap* editor, SDL_Event* event);

void editor_tile_map_render(EditorTileMap* editor, SDL_Renderer* renderer);

void editor_tile_map_update(EditorTileMap* editor, float delta_time);

#endif
