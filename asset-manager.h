// images: png
// music: ogg vorbis 44.1kHz
// sound effects: wav

// load assets via threads
typedef enum {
	ASSET_TEXTURE_GRASS,
	ASSET_TEXTURE_SWORD,
	
	ASSET_TEXTURE___NUM
} ASSET_TEXTURE_ID;

inline SDL_Texture* get_texture(GameState* game_state, ASSET_ID id)
{
	return game_state->assets[id];	
}

inline void draw_texture(GameState, ASSET_ID id)
{
	if (id < 0 || id >= ASSET__NUM) {
		
	}
	SDL_RenderCopyEx();	
}

typedef struct {
	SDL_Texture *textures[ASSET_NUM]; // as accessing memory, should use getters and setters
	TTF_Font *fonts[];
	MIX_Music *music[];
} Assets;

void load_textures()

typedef struct {

} GameState;


int main(void)
{
	game_state->assets[ASSET_GRASS] = load_texture("grass.bmp");	

	return 0;	
}
