#include "tilemap.h"

#include "layer.h"
#include "config.h"

EditorTileMap* editor_tilemap_create(unsigned tile_render_width, unsigned tile_render_width) // stbte_create_map()
{
	EditorTileMap* tile_map = xmalloc(sizeof(EditortTileMap));

	tile_map->tile_render_width = tile_render_width;
	tile_map->tile_render_height = tile_render_height;

	for (size_t layer_index = 0; layer_index < EDITOR_LAYERS_MAX; ++layer_index) {
		tile_map->layers[layer_index].is_hidden = false;
		tile_map->layers[layer_index].is_locked = false;
		tile_map->layers[layer_index].name = "";
	}

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
			for (size_t layer_index = 0; layer_index < EDITOR_LAYERS_MAX; ++layer_index) {
				if (layer_index == 0) {
					tilemap->tile_data[y][x][layer_index] = tilemap->background_tile;
				} else {
					tilemap->tile_data[y][x][layer_index] = NO_TILE;
				}
			}	

			for (size_t property_index = 0; property_index < EDITOR_PROPERTIES_MAX; ++property_index) {
				tilemap->tile_data[y][x][property_index] = 0;
			}

			tilemap->tile_links[y][x].x = -1;
			tilemap->tile_links[y][x].y = -1;
			tilemap->tile_links_count[y][x].y = 0;
		}	
	}	
}

static void tilemap_add_tile(EditorTilemap* tilemap, int id, unsigned layermask, const char* category)
{
	tilemap->tile_data[tilemap->tiles_in_use].category = (char *)category;	

}




