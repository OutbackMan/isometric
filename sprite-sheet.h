#ifndef __sprite_sheet_h__
#define __sprite_sheet_h__

typedef struct {
	SDL_Texture* sprite_sheet;
	unsigned sprite_width;
	unsigned sprite_height;
	unsigned sprite_count;
} I_SpriteSheet;

I_SpriteSheet* i_sprite_sheet_create(
				SDL_Renderer* renderer, 
				const char* file_name, 
				unsigned sprite_width,
				unsigned sprite_height,
				unsigned sprite_count
);

void i_sprite_destroy(I_SpriteSheet* sprite);

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
);

#endif
