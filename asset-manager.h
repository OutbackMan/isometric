// images: png
// music: ogg vorbis 44.1kHz
// sound effects: wav
/*
int x =
	10;
*/
// load assets via threads
#define BIT(amount) amount
#define BYTE(amount) (8 * BIT(amount))
#define KILOBYTES(amount) (1000 * BYTE(amount))

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
	} else {
		assets_texture_load(assets, texture_id);
	}
	
}

typedef struct {
	Assets* assets;
	const char* file_name;
	TEXTURE_ASSET_ID texture_id;
} LoadAssetWork;
INTERNAL WORK_QUEUE_CALLBACK(load_asset_work)
{
	LoadAssetWork* work = (LoadAssetWork *)data;
	work->assets->textures[work->texture_id] = SDL_LoadTexture(work->file_name);
}

void assets_texture_load(Assets* assets, ASSET_TEXTURE_ID texture_id)
{
	LoadAssetWork* work;
	work->assets = assets;
	work->texture_id = texture_id;
	
	work_queue_add_entry(queue, load_asset_work);
	
	switch (texture_id) {
	case TEXTURE_SWORD:
		assets->file_name = "sword.png";
		break;
	}
	
}



int main(void)
{
	return 0;	
}
