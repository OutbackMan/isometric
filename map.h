typedef struct {
	I_SpriteSheet* tile_sheet;	
	size_t num_tiles_x;
	size_t num_tiles_y;
	I_Map__TileDescriptor* tile_descriptors;
} I_Map;

typedef struct {
	int tile_index;
	bool is_solid;
} I_Map__TileDescriptor;
