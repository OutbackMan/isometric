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
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* window = SDL_CreateWindow("name", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SHOW);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

SDL_Surface* red_surface = SDL_LoadBMP("red.bmp");
SDL_Texture* red_texture = SDL_CreateTextureFromSurface(renderer, red_surface);
SDL_FreeSurface(red_surface);
SDL_Surface* green_surface = SDL_LoadBMP("green.bmp");
SDL_Texture* green_texture = SDL_CreateTextureFromSurface(renderer, green_surface);
SDL_FreeSurface(green_surface);
SDL_Surface* blue_surface = SDL_LoadBMP("blue.bmp");
SDL_Texture* blue_texture = SDL_CreateTextureFromSurface(renderer, blue_surface);
SDL_FreeSurface(blue_surface);

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
	stbte_tilemap* tile_map = stbte_create_map(int map_x, int map_y, int map_layers, int spacing_x, int spacing_y, int max_tiles);
	
	stbte_define_tile(tile_map, unsigned short id, unsigned int layermask, const char * category);
	stbte_define_tile(tile_map, unsigned short id, unsigned int layermask, const char * category);
	stbte_define_tile(tile_map, unsigned short id, unsigned int layermask, const char * category);
	
	stbte_set_display(int x0, int y0, int x1, int y1);
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event->type) {
		SDL_MOUSEMOVE, SDL_MOUSEBUTTON, SDL_MOUSEWHEEL
		stbte_mouse_sdl(stbte_tilemap *tm, const void *sdl_event, float xscale, float yscale, int xoffset, int yoffset);
		}
	}

	stbte_tick(stbte_tilemap *tm, float time_in_seconds_since_last_frame);
	
	stbte_draw(stbte_tilemap *tm);
	
	return 0;
}


SDL_DestroyTexture(red_texture);
SDL_DestroyTexture(green_texture);
SDL_DestroyTexture(blue_texture);
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
