typedef struct {
	void** keys;
	void** values;
	size_t length;
	size_t capacity;
} Map;

uint64_t ptr_hash(void* ptr)
{
	return (uint64_t)(ptr);
}

void* map_get(Map* map, const void* key)
{
	SDL_assert(key != NULL); // NULL is our sentinel value
	if (map->length == 0) return NULL;

	uint64_t hash = ptr_hash(key);	
}

Map* map_create()
{
	
}
