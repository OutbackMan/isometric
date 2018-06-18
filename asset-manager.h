// images: png
// music: ogg vorbis 44.1kHz
// sound effects: wav
/*
int x =
	10;
*/
// load assets via threads

typedef enum {
	TEXTURE_GRASS,
	TEXTURE_STONE,
	TEXTURE_WOOD,
	TEXTURE__NUM
} ASSET_TEXTURE_ID;

typedef struct {
	SDL_Texture *textures[TEXTURE__NUM];
	TTF_Font *fonts[];
	MIX_Music *music[];
} Assets;

inline SDL_Texture* assets_texture_get(Assets* assets, ASSET_TEXTURE_ID texture_id)
{
	return assets->textures[texture_id];
}

void assets_texture_render(Assets* assets, ASSET_TEXTURE_ID texture_id)
{
	if (assets_texture_get(assets, texture_id) != NULL) {
		SDL_RenderCopyEx();
	}
	
}

void assets_texture_load(Assets* assets)
{
	assets->textures[TEXTURE_SWORD] = SDL_LoadText("sword.png");
}


int main(void)
{
	game_state->assets[ASSET_TEXTURE_GRASS] = load_texture(ASSET_TEXTURE_GRASS);	

	return 0;	
}
