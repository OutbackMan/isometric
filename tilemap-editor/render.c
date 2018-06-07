#include "render.h"

#include <SDL2/SDL.h>

#include "config.h"
#include "editor.h"

// editor_traverse()
void editor_render(Editor* editor, SDL_Renderer* renderer)
{
	render_editor_background(editor, renderer);

	render_editor_tilemap(editor, renderer);
}

static void render_editor_background(SDL_Renderer* renderer)
{
	_SDL_SetRenderDrawColor(renderer, EDITOR_BACKGROUND_COLOR); // _SDL --> direct wrapper
	_SDL_RenderFillRect(renderer, NULL);
}

static void render_editor_tilemap(SDL_Renderer* renderer)
{
	// START(background)
	int x0 = 0 - tile_map->input_values->scroll_x;
	int y0 = 0 - tile_map->input_values->scroll_y;
	int x1 = tile_map->tile_spacing_x * tile_map->num_tiles_x; 
	int y1 = tile_map->tile_spacing_y * tile_map->num_tiles_y; 

	__SDL_RenderRect(renderer, x0, y0, x1, y1, TILEMAP_BACKGROUND_COLOR); // __SDL --> indirect wrapper
	// END(background)

	// START(tiles)	
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
			render_tile(tile_map, tile_x, tile_y, render_x, render_y);
		}
	}
	// END(tiles)	

	// START(grid)
	int x = visible_tile_x * tile_map->spacing_x - tile_map->scroll_x;		
	int y = visible_tile_y * tile_map->spacing_y - tile_map->scroll_y;		
	for (int i = 0; i < width_width && i <= num_visible_tiles_x; ++i, x += tile_map->spacing_x) {
		_SDL_RenderDrawRect(renderer, x, 0, x + 1, window_height, COLOR_GRID);	
	}
	for (int j = 0; j < width_height && j <= num_visible_tiles_y; ++j, y += tile_map->spacing_y) {
		_SDL_RenderDrawRect(renderer, 0, y, window_width, y + 1, COLOR_GRID);	
	}
	// END(grid)
	
	// START(more_tiles)
	more_tile(); // stbte_tile
	// END(more_tiles)

}

static void more_tile()
{
	
}

static void render_tile(SDL_Renderer* renderer, int tile_x, int tile_y, int render_x, int render_y)
{
	int x0 = render_x;
	int y0 = render_y;
	int x1 = x0 + tile_map->spacing_x;
	int y1 = y0 + tile_map->spacing_y;

	if (MAP_IS_HOT) {
		if (editor->is_pasting) {
			int ox = tile_x - editor->paste_x;		
			int oy = tile_y - editor->paste_y;
			if (ox >= 0 && ox < editor->copy_width && oy >= 0 && oy < editor->copy_height) {
				paste_stack();		
			}
		}		
	}
}

void draw_tilemap()
{
	draw_background();	
	draw_tiles();
	draw_grid();
	draw_selection_border();
}


static void editor_traverse()
{
	draw_editor_background();

	draw_tilemap();

	draw_panels();

	draw_regions();
}


void draw_panels()
{
	compute_panel_locations(editor);

	draw_panel_bodies();
	draw_panel_selectors();
	draw_panel_expanders();
}

static void compute_panel_locations(Editor* editor)
{
	for (size_t region_index = 0; region_index < 4; ++region_index) {
		editor->region[region_index].is_active = false;		
		editor->region[region_index].width = 0;		
		editor->region[region_index].height = 0;		
	}	

	compute_digits();

	min_width[PANEL_INFO]
	min_width[PANEL_TILES]
	min_width[PANEL_TOOLBAR]
}
