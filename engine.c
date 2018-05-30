#include "engine.h"

I_Map* i_map_create(int tile_width, int tile_height)
{
	I_Map* map = i_common_xmalloc(sizeof(I_Map));	

	map->tile_width = tile_width;
	map->tile_height = tile_height;
	// ...
}
