#include "tilemap.h"

#include "sprite-sheet.h"
#include "config.h"

EditorTileMap* editor_tilemap_create(unsigned tile_render_width, unsigned tile_render_width, SpriteSheet* sprite_sheet)
{
	EditorTileMap* tile_map = xmalloc(sizeof(EditortTileMap));

	static const size_t STARTING_NUM_TILES_X = 200;
	static const size_t STARTING_NUM_TILES_Y = 200;

	tile_map->num_tiles_x = STARTING_NUM_TILES_X;
	tile_map->num_tiles_y = STARTING_NUM_TILES_Y;
	tile_map->current_placed_tile_index = 0;

	tile_map->tile_palette = sprite_sheet;

	tile_map->tile_render_width = tile_render_width;
	tile_map->tile_render_height = tile_render_height;

	tile_map->restore_system = restore_system_create();

	tilemap_init(tile_map);

	return tile_map;
}

static void tilemap_init(EditorTileMap* tile_map)
{
	for (size_t map_x = 0; map_x < tile_map->num_tiles_x; ++map_x) {
		for (size_t map_y = 0; map_y < tile_map->num_tiles_y; ++map_y) {
			tile_map->tiles[map_y * tile_map->num_tiles_x + map_x] = 0;	
		} 
	} 
}
