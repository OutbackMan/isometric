#include "tilemap.h"

#include "sprite-sheet.h"
#include "config.h"


///////////////////////////////
// START(CONSTRUCTOR)
///////////////////////////////
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
///////////////////////////////
// END(CONSTRUCTOR)
///////////////////////////////


///////////////////////////////
// START(DESTRUCTOR)
///////////////////////////////
///////////////////////////////
// END(DESTRUCTOR)
///////////////////////////////


///////////////////////////////
// START(EVENTS)
///////////////////////////////
void editor_tile_map_events(EditorTileMap* tile_map, SDL_Event* event, Editor__InputValues* editor_input_values)
{
	tile_map_events_keyboard();

	switch (event->type) {
	case SDL_MOUSEMOTION:
		if (editor_input_values->tile_map_want_to_scroll) {
			editor_input_values->tile_map_scroll_x += (editor_input_values->start_x - editor_input_values->mouse_x);
			editor_input_values->tile_map_scroll_y += (editor_input_values->start_y - editor_input_values->mouse_y);
			editor_input_values->start_x = editor_input_values->mouse_x;
			editor_input_values->start_y = editor_input_values->mouse_y;
		}
	}	
}

void tile_map_events_keyboard()
{
	const SDL_Keymod keyboard_modifiers = SDL_GetModState();
	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);
	
}
///////////////////////////////
// END(EVENTS)
///////////////////////////////


///////////////////////////////
// START(UPDATE)
///////////////////////////////
///////////////////////////////
// END(UPDATE)
///////////////////////////////


///////////////////////////////
// START(RENDER)
///////////////////////////////
void editor_tile_map_render(EditorTileMap* tile_map, Editor__InputValues* editor_input_values, SDL_Renderer* renderer)
{
	tile_map_render_bg();		
}

static void tile_map_render_bg()
{
	int tile_map_x0 = 0 - editor_input_values->tile_map_scroll_x;
	int tile_map_y0 = 0 - editor_input_values->tile_map_scroll_y;
	int tile_map_x1 = tile_map->tile_render_width * tile_map->num_tiles_x; 
	int tile_map_y1 = tile_map->tile_render_height * tile_map->num_tiles_y; 

	__SDL_RenderQuadFill(
				renderer, 
				tile_map_x0, 
				tile_map_y0, 
				tile_map_x1, 
				tile_map_y1, 
				EDITOR_CONFIG_COLOUR_TILE_MAP_BG
			);
}

static void tile_map_render_tiles()
{
	int visible_tile_x = (tile_map->input_values->scroll_x - tile_map->tile_spacing_x) / tile_map->tile_spacing_x;
	int visible_tile_y = (tile_map->input_values->scroll_y - tile_map->tile_spacing_y) / tile_map->tile_spacing_y;
	int num_visible_tiles_x = (tile_map->input_values->scroll_x + window_width) / tile_map->tile_spacing_x;
	int num_visible_tiles_y = (tile_map->input_values->scroll_y + window_height) / tile_map->tile_spacing_y;

	if (visible_tile_x < 0) visible_tile_x = 0;	
	if (visible_tile_y < 0) visible_tile_y = 0;	
	if (num_visible_tiles_x > tile_map->num_tiles_x) num_visible_tiles = tile_map->num_tiles_x;
	if (num_visible_tiles_y > tile_map->num_tiles_y) num_visible_tiles = tile_map->num_tiles_y;

	for (int tile_x = visible_tile_x; tile_count < num_visible_tiles_x; ++tile_count) {
		for (int tile_y = visible_tile_y; tile_count < num_visible_tiles_y; ++tile_count) {
			int render_x = tile_x * tile_map->spacing_x - tile_map->input_values->scroll_x;
			int render_y = tile_y * tile_map->spacing_y - tile_map->input_values->scroll_y;
			render_tile(tile_map, tile_x, tile_y, render_x, render_y); // tile_paint
		}
	}
}

///////////////////////////////
// END(RENDER)
///////////////////////////////
