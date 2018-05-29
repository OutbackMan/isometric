#include "common.h"

#include <SDL2/SDL.h>

#include <stdlib.h>

void i_common_exit(int exit_status)
{
	SDL_Quit();
	exit(exit_status);
}

void* i_common_xmalloc(size_t num_bytes)
{
	void* ptr = malloc(num_bytes);	
	if (ptr == NULL) {
		perror("malloc() call failed");
		SDL_Quit();
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}

void* i_common_xcalloc(size_t num_elements, size_t element_size)
{
	void* ptr = calloc(num_elements, element_size);	
	if (ptr == NULL) {
		perror("calloc() call failed");
		SDL_Quit();
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}

void* i_common_xrealloc(void* ptr, size_t num_bytes)
{
	ptr = realloc(ptr, num_bytes);
	if (ptr == NULL) {
		perror("realloc() call failed");
		SDL_Quit();
		exit(EXIT_FAILURE);
	} else {
		return ptr;		
	}
}
