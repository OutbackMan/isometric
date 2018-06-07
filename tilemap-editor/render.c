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
	int x0 = -scroll_x;
	int y0 = -scroll_y;
	int x1 = -scroll_x + spacing_x * max_x; 
	int y1 = -scroll_y + spacing_y * max_y; 

	__SDL_RenderRect(renderer, x0, x1, y0, y1, TILEMAP_BACKGROUDN_COLOR); // __SDL --> indirect wrapper
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
