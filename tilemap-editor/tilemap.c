#include "tilemap.h"

#include "config.h"

EditorTileMap* editor_tilemap_create(unsigned tile_render_width, unsigned tile_render_width)
{
	EditorTileMap* tile_map = xmalloc(sizeof(EditortTileMap));

	tile_map->tile_render_width = tile_render_width;
	tile_map->tile_render_height = tile_render_height;

	tile_map->background_tile = NO_TILE;

	tilemap_clear(tile_map);

	tile_map->tiles_in_use = 0;
	tile_map->tileinfo_is_dirty = true;

	return tile_map;
}

static void tilemap_clear(EditorTilemap* tilemap)
{
	for (size_t map_y = 0; map_y < EDITOR_TILEMAP_MAX_HEIGHT; ++map_y) {
		for (size_t map_x = 0; map_x < EDITOR_TILEMAP_MAX_WIDTH; ++map_x) {
			for (size_t property_index = 0; property_index < EDITOR_PROPERTIES_MAX; ++property_index) {
				tilemap->tile_data[y][x][property_index] = 0;
			}

			tilemap->tile_links[y][x].x = -1;
			tilemap->tile_links[y][x].y = -1;
			tilemap->tile_links_count[y][x].y = 0;
		}	
	}	

	for (size_t tile_count = 0; tile_count < tilemap->max_tiles; ++tile_count) {
		tilemap->id_in_use[tile_count] = 0;		
	}
}

void editor_tilemap_define_tile(EditorTilemap* tilemap, int tile_id, const char* tile_category)
{
	if (tilemap->available_tiles >= tilemap->max_tiles) { return; }

	tilemap->id_in_use[tilemap->available_tiles] = tile_id;

	tilemap->tiles[tilemap->available_tiles].category = (char *)tile_category;
	tilemap->tiles[tilemap->available_tiles].id = tile_id;

	++tilemap->available_tiles;
	tilemap->tileinfo_dirty = 1;
}
