#include "editor.h"

int main(void)
{
	Editor* editor = editor_create();

	editor_events(editor, event);

	editor_update();

	editor_render();

	editor_destroy(editor);

	return 0;	
}

////////////////////////////////////////////////////////////////////

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* red_texture = NULL;
SDL_Texture* green_texture = NULL;
SDL_Texture* blue_texture = NULL;

const unsigned short RED_TILE = 0;
const unsigned short GREEN_TILE = 1;
const unsigned short BLUE_TILE = 2;

#define STB_TILEMAP_EDITOR_IMPLEMENTATION

void STBTE_DRAW_RECT(int x0, int y0, int x1, int y1, uint color)
{
	SDL_SetRenderDrawColor(renderer, color<<16, color<<8, color, 0xff);
	SDL_Rect render_rect = { x0, y0, x1 - x0, y1 - y0 };
	SDL_RenderFillRect(renderer, &render_rect);
}

void STBTE_DRAW_TILE(int x0, int y0, unsigned short id, int highlight, float *data)
{
	SDL_Rect render_rect = { 0, 0, tile_width, tile_height };
	switch (id) {
	case RED_TILE:
		SDL_RenderCopy(renderer, red_texture, NULL, &render_rect);
	case GREEN_TILE:
		SDL_RenderCopy(renderer, green_texture, NULL, &render_rect);	
	case BLUE_TILE:
		SDL_RenderCopy(renderer, blue_texture, NULL, &render_rect);		
	}
	(void)(sizeof(highlight));
	(void)(sizeof(data));
}

#include "stbte_tilemap_editor.h"

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("name", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOW);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	SDL_Surface* red_surface = SDL_LoadBMP("red.bmp");
	red_texture = SDL_CreateTextureFromSurface(renderer, red_surface);
	SDL_FreeSurface(red_surface);
	SDL_Surface* green_surface = SDL_LoadBMP("green.bmp");
	green_texture = SDL_CreateTextureFromSurface(renderer, green_surface);
	SDL_FreeSurface(green_surface);
	SDL_Surface* blue_surface = SDL_LoadBMP("blue.bmp");
	blue_texture = SDL_CreateTextureFromSurface(renderer, blue_surface);
	SDL_FreeSurface(blue_surface);
	
	
	
	// x, y, layers, render_width, render_height, max_tiles
	stbte_tilemap* tile_map = stbte_create_map(0, 0, 3, 2, 2, 500);
	
	stbte_define_tile(tile_map, RED_TILE, 0, NULL);
	stbte_define_tile(tile_map, GREEN_TILE, 0, NULL);
	stbte_define_tile(tile_map, BLUE_TILE, 0, NULL);
	
	stbte_set_display(0, 0, 200, 200);
	float prev_time = SDL_GetTicks();
	
	bool want_to_run = true;
	while (want_to_run) {
		float cur_time = prev_time - SDL_GetTicks();
		prev_time = cur_time;
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event->type) {
			case SDL_QUIT:
				want_to_run = false;
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				// xscale, yscale, xoffset, yoffset
				stbte_mouse_sdl(tile_map, &event, 2, 2, 0, 0);
				break;
			}
		}

		stbte_tick(tile_map, cur_time);

		stbte_draw(tile_map);
	}
	
	SDL_DestroyTexture(red_texture);
	SDL_DestroyTexture(green_texture);
	SDL_DestroyTexture(blue_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}



