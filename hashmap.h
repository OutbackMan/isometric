// 21:00

// utilise linear probing to resolve collisions, i.e. place into next available slot
// array almost always better than linked list as stored continguosly

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

void* map_get(Map* map, void* key, uint64_t hash_code)
{
	SDL_assert(key != NULL); // NULL is our sentinel value
	if (map->length == 0) return NULL;

	size_t i = hash_code % map->capacity;
	// SDL_assert(map->length < map->capacity); so we always have a NULL terminator

	while (true) {
		if (map->keys[i] == key) {
			return map->values[i];	
		} else if (map->keys[i] == NULL) {
			return NULL;	
		}
		i++;
	}
	
	return NULL;
}

void map_grow(Map* map, size_t new_capacity)
{
	void* mem = i_common_xmalloc(2 * new_capacity * sizeof(void *));	
	Map new_map = {
		.keys = mem,
		.values = mem + new_capacity * sizeof(void *)
		.capacity = new_capacity
	};

	for (size_t i = 0; i < map->capacity; ++i) {
		if (map->keys[i]) {
			map_put(&new_map, map->keys[i], map->values[i]);	
		}	
	}

	free(map->keys); // handles both keys and values due to single allocation

	*map = new_map;
}

void* map_put(Map* map, void* key, void* value)
{
	if (map->length * 2 >= map->capacity) {
		map_grow(map, map->capacity * 2);		
	}	
}

Map* map_create()
{
	
}
