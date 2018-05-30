#include "map.h"

// <num_tiles_x> <num_tiles_y> <tilesheet> [<index> <solid>] ...
I_Map* i_map_create(const char* map_file_name)
{
	FILE* map_file = fopen(map_file_name, "rb");		

	if (map_file == NULL) {
		i_set_error(ENOFILE);		
		return NULL;
	} else {
		I_Map* map = i_common_xmalloc(sizeof(I_Map));		
		map->tile_descriptors = i_common_xmalloc(
									sizeof(I_Map__TileDescriptors) * width * height
								);

		fclose(map_file);

		return map;
	}
}

void i_map_create(I_Map* map)
{
	// have a pool for textures
	free(map->tile_descriptors);
	free(map);
}

void i_map_draw(I_Map* map, size_t tile_render_width, size_t tile_render_height)
{
}
