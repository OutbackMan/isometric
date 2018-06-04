#include "tilemap.h"

#include "layer.h"
#include "info.h"

EditorTileMap* editor_tilemap_create(unsigned tile_render_width, unsigned tile_render_width)
{
	EditorTileMap* tile_map = xmalloc(sizeof(EditortTileMap));

	tile_map->background_tile = NO_TILE;

	tile_map->tile_render_width = tile_render_width;
	tile_map->tile_render_height = tile_render_height;

	for (size_t layer_index = 0; layer_index < EDITOR_LAYERS_MAX; ++layer_index) {
		tile_map->layers[layer_index].is_hidden = false;
		tile_map->layers[layer_index].is_locked = false;
		tile_map->layers[layer_index].name = "";
	}

	return tile_map;
}
