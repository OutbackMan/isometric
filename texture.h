#ifndef __texture_h__
#define __texture_h__

typedef struct {
	int x;
	int y;
	int width;
	int height;
	double angle;
	SDL_Point* centre;
	SDL_Rect* clip_rect;
	SDL_RendererFlip flip_type;
	SDL_Texture* texture;
} I_Texture;

#endif
