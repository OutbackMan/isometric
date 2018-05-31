typedef struct {
	Map* texture_map; // music, fonts, etc.
} AssetManager;

create

get
void asset_manager_set_texture(const char* key_name, const char* texture_location)
{
	SDL_Texture* texture = i_common_load_texture(texture_location);

	asset_manager->map(key_name, texture);
}

destroy
