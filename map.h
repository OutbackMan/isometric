#ifndef __map_h__
#define __map_h__

#include <SDL2/SDL.h>

#include <stddef.h>

typedef struct {
	int tile_index;
	bool is_solid;
} I_Map__TileDescriptor;

typedef struct {
	I_SpriteSheet* tile_sheet;	
	size_t num_tiles_x;
	size_t num_tiles_y;
	I_Map__TileDescriptor* tile_descriptors;
} I_Map;

#endif
