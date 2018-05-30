#include "sprite-sheet.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common.h"

I_SpriteSheet* i_sprite_sheet_create(
				SDL_Renderer* renderer, 
				const char* file_name, 
				unsigned sprite_width,
				unsigned sprite_height,
				unsigned sprite_count
)
{
	I_SpriteSheet* sprite_sheet = i_common_xmalloc(sizeof(I_SpriteSheet));

	SDL_Surface* sprite_sheet_surface = IMG_Load(file_name);

	if (sprite_sheet_surface == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to create I_SpriteSheet surface %s", 
			IMG_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	sprite_sheet->sprite_sheet = SDL_CreateTextureFromSurface(renderer, sprite_sheet_surface);
	SDL_FreeSurface(sprite_sheet_surface);

	if (sprite_sheet == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to convert I_SpriteSheet surface to texture %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}
	
	sprite_sheet->sprite_sheet = sprite_sheet_texture;
	sprite_sheet->sprite_count = sprite_count;
	sprite_sheet->sprite_width = sprite_width;
	sprite_sheet->sprite_height = sprite_height;
	
	return sprite_sheet;
}

void i_sprite_sheet_destroy(I_SpriteSheet* sprite_sheet)
{
	SDL_DestroyTexture(sprite_sheet->sprite_sheet);	
	free(sprite_sheet);
}

void i_sprite_sheet_draw(
			I_SpriteSheet* sprite_sheet,
			SDL_Renderer* renderer,
			I_Map* map,
			int sprite_index,
			int x, 
			int y, 
			double draw_angle,
			SDL_Point* draw_centre,
			SDL_RendererFlip draw_filp_type
)
{
	int sheet_x_index = sprite_index * sprite_sheet->sprite_width;

	SDL_Rect sprite_clip = { 
		.x = sheet_x_index, 
		.y = 0, 
		.w = sprite_sheet->sprite_width, 
		.h = sprite_sheet->sprite_height 
	};

	SDL_Rect sprite_render_clip = { 
		.x = x, 
		.y = y, 
		.w = map->tile_width, 
		.h = map->tile_height 
	};

	SDL_RenderCopyEx(
			renderer, 
			sprite_sheet, 
			&sprite_clip, 
			&sprite_render_clip, 
			draw_angle,
			draw_centre,
			draw_flip_type
	);

}

/*
 car.h
 enum { I_SPRITESHEET_INDEX_CAR_MERCEDES, ... };
 enum { I_SPRITESHEET_DIRECTION_CAR_MERCEDES_LEFT = 90 };
 car-64-64-5.png
*.
