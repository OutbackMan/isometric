#ifndef __text_input_h__
#define __text_input_h__

// SDL_TEXTEDITING will process composite keys, i.e. certain keys to yield particular characters (marked_text ??)
// SDL_TEXTINPUT will yield the final character

typedef struct {
	const char* string;
	bool entered;
	bool escaped;
	uint8_t input_buffer[8000];
} TextInput;
// TTF_RenderUTF8_Blended

char utf8_input_text[8000], marked_text[SDL_TEXTEDITINGEVENT_TEXT_SIZE]; 
int cursor_column = 0;
SDL_Rect input_text_rect, marked_rect;

void init_input()
{
	input_text_rect = {
		.x = 100,
		.y = 100,
		.w = 300,
		.h = 50
	};
	marked_rect = input_text_rect;

	utf8_input_text[0] = '\0';
	marked_text[0] = '\0';

	SDL_StartTextInput(); // so we can capture events. SDL_StopTextInput()
}

void draw()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	
	// draw input area
	SDL_RenderFillRect(renderer, &input_text_rect);

	// draw recieved text
	SDL_Surface* input_text_surface = TTF_RenderUTF8_Blended(font, utf8_input_text, colour);
	SDL_Texture* input_text_texture = SDL_CreateTextureFromSurface(renderer, input_text_surface);
	SDL_Rect input_text = {
		.x = text_rect.x,
		.y = text_rect.y,
		.w = input_text_surface->w,
		.h = input_text_surface->h
	};
	SDL_RenderCopy(renderer, input_text_texture, NULL, &input_text_rect);

	int input_text_width;
	int input_text_height;
	TTF_SizeUTF8(font, utf8_input_text, &input_text_width, &input_text_height);
}

void events(SDL_Event* event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
		case SDLK_RETURN:		
			console->input_text[0] = 0x00;
			// ...
		case SDLK_BACKSPACE:
			size_t input_text_length = strlen(input_text);
				
			const char MSB_1_SET_MASK = 0x80;
			const char MSB_1_2_SET_MASK = 0xc0;

			do {
				if (input_text_length == 0) {
					break;		
				}	
				if (input_text[input_text_length - 1] & MSB_1_SET_MASK == 0x00) {
					// single byte
					input_text[input_text_length - 1] = '\0';
					break;
				}
				if (input_text[input_text_length - 1] & MSB_1_2_SET_MASK == MSB_1_SET_MASK) {
					// byte from multibyte sequence
					input_text[input_text_length - 1] = '\0';
					input_text_length--;
				}
				if (input_text[input_text_length - 1] & MSB_1_2_SET_MASK == MSB_1_2_SET_MASK) {
					// first byte from multibyte sequence
					input_text[input_text_length - 1] = '\0';
					break;
				}

			} while (true);
			break;
		case SDL_TEXTINPUT:
			if (strlen(input_text) + strlen(event->text.text) < sizeof(input_text)) {
				strcat(input_text, event->text.text);		
			}
		case SDL_TEXTEDITING:
	}
}

#endif
