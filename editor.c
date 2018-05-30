// d2dfactory -> rendertarget (begindraw, ...)

// 1:23

TTF_Init();
TTF_Font* font = TTF_OpenFont("arial.ttf", 25);

SDL_Surface* text_surface = TTF_RenderText_Solid(font, "text", (SDL_Colour){0xff, 0xff, 0xff, 0xff});
SDL_Texture* text_texture = SDL_CreateTextureFromSurface(local_play_surface);
SDL_FreeSurface(text_surface);

SDL_DestroyTexture(text_texture);
TTF_CloseFont(font);
TTF_Quit();

/*
gap buffer will position 'free memory' at cursor position to allow for amortised insertions and deletions. (a traditional vector will have this gap at the end)
<---------------------------------------------------------------------->
[        C          ]              [                                   ]
                    <-------------->
				   gap_start | gap_end
*/

typedef struct {
	char* name;
	char* data;
	uint32_t cursor_position;
	uint32_t gap_start_position;
	uint32_t gap_end_position;
	uint32_t end_position;
} Buffer;

Buffer* buffer_create(int gap_size)
{
	Buffer* buffer = xmalloc(sizeof(Buffer));	

	buffer->data = xmalloc(sizeof(char) * gap_size);
	buffer->cursor_position = 0;
	buffer->gap_start_position = 0;
	buffer->gap_end_position = gap_size;
	buffer->end_position = 0;

	return buffer;
}

void buffer_shift_gap_to_cursor(Buffer* buffer)
{
	uint32_t distance_to_shift;

	if (buffer->cursor_position < buffer->gap_start_position) {
		distance_to_shift = buffer->gap_start_position - buffer_cursor_position;	

		memmove(buffer->data + buffer->gap_end_position - distance_to_shift, buffer->data + buffer->cursor_position, distance_to_shift);   

		buffer->gap_start_position -= distance_to_shift;
		buffer->gap_end_position -= distance_to_shift;
	} else if (buffer->cursor_position > buffer->gap_start_position) {
		distance_to_shift = buffer_cursor_position - buffer->gap_start_position;

		memmove(buffer->data + buffer->gap_start_position, buffer->data + buffer->cursor_position, distance_to_shift);   

		buffer->gap_start_position += distance_to_shift;
		buffer->gap_end_position += distance_to_shift;
	} else {
		return;		
	}
}

void buffer_ensure_gap_size(Buffer* buffer, int min_gap_size)
{
	uint32_t current_gap_size = buffer->gap_end_position - buffer->gap_start_position;
	if (current_gap_size < min_gap_size) {
		
	}
}

void buffer_insert(Buffer* buffer, char character)
{
	buffer_shift_gap_to_cursor(buffer);
	buffer_ensure_gap_size(buffer, 1);

	buffer->data[buffer->gap_start_position++] = character;	
	buffer->cursor_position++, buffer->gap_end_position++;
}

void buffer_render(Buffer* buffer)
{
	
}


