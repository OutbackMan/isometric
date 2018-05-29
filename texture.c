#include "texture.h"

I_Texture* i_texture_create(
				SDL_Renderer* renderer, 
				const char* file_name, 
				int x, 
				int y,
				double angle,
				SDL_Point* centre,
				SDL_Rect* clip_rect,
				SDL_RendererFlip flip_type
)
{
	I_Texture* texture = i_common_xmalloc(sizeof(I_Texture));

	SDL_Surface* texture_surface = IMG_Load(file_name);

	if (texture_surface == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to create surface %s", 
			IMG_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	texture->texture = SDL_CreateTextureFromSurface(renderer, texture_surface);
	SDL_FreeSurface(texture_surface);

	if (texture == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to convert surface to texture %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}

	if (SDL_QueryTexture(texture->texture, &texture->width, &texture->height) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to query texture %s", 
			SDL_GetError()
		);
		i_common_exit(EXIT_FAILURE);
	}
	
	texture->x = x;
	texture->y = y;
	texture->angle = angle;
	texture->centre = centre;
	texture->clip_rect = clip_rect;
	texture->flip_type = flip_type
	
	return texture;
}

void i_texture_destroy(I_Texture* texture)
{
	SDL_DestroyTexture(texture->texture);	
	free(texture);
}

void i_texture_render_xy_clip(I_Texture* texture, )
{
	SDL_assert(texture != NULL);	


}
