#ifndef __console_h__
#define __console_h__

// 2:00:00

typedef enum {
	CLOSED,
	OPEN_SMALL,
	OPEN_BIG
} CONSOLE_STATE; // extent

typedef struct {
	TTF_Font* input_font;
	TTF_Font* report_font;

	SDL_Colour* input_bg_colour;
	SDL_Colour* input_text_colour;
	SDL_Colour* report_bg_colour;
	SDL_Colour* report_text_colour;

	float current_render_height_fraction; // open_t
	float desired_render_height_fraction; // open_t_target
	float render_height_fraction_delta; // dopen_dt

	TextInput* text_input;

	STRETCHY_BUF(const char *) history; // all the strings that we draw
} Console;

// asset_manager->fonts[CONSOLE_INPUT_FONT];
Console* console_create(
			TTF_Font* input_font, 
			TTF_Font* report_font, 
			SDL_Colour* input_bg_colour, 
			SDL_Colour* input_text_colour, 
			SDL_Colour* report_bg_colour, 
			SDL_Colour* report_text_colour
)
{
	Console* console = xmalloc(sizeof(Console));	

	console->input_font = input_font;
	console->report_font = report_font; 

	console->input_bg_colour = input_bg_colour; 
	console->input_text_colour = input_text_colour; 
	console->report_bg_colour = report_bg_colour;
	console->report_text_colour = report_text_colour;

	console->current_render_height_fraction = 0.0f;
	console->desired_render_height_fraction = 0.0f;
	console->render_height_delta = 1.0f;

	STRETCHY_BUF_PUSH(console->history, "Hello there!");
	STRETCHY_BUF_PUSH(console->history, "This is a confusing message");

	return console;
}

void console_destroy(Console* console)
{
	STRETCHY_BUF_FREE(console->history);	
	free(console);
}


void console_draw(Console* console)
{
	update_height(console);	

	cursor_in_output = false;

	float current_height = get_current_height();	

	const SDL_Rect input_render_rect = {
		.x = 0,
		.y = 0,
		.w = renderer->logical_width,
		.h = current_height 
	};
	SDL_RenderSetDrawColor(renderer, console->input_bg_colour->r); // ... create wrapper
	SDL_RenderFillRect(renderer, &input_render_rect);

	const SDL_Rect report_render_rect = {
		.x = 0,
		.y = current_height,
		.w = renderer->logical_width,
		.h = current_height + console->report_font->height
	};
	SDL_RenderSetDrawColor();
	SDL_RenderFillRect(renderer, &report_render_rect);

	// draw text now
	int text_x = console->report_font->height * 0.5;
	int text_y = current_height; 
	
	int text_index = STRETCHY_BUF_LEN(console->history) - 1;
	while (text_y >= 0) {
		if (text_index < 0) break;	

		SDL_Surface* text_surface = TTF_RenderText_Solid(console->history[text_index]); // wrapper
		SDL_RenderCopy(text_texture, text_x, text_y, NULL);

		--index;
		text_y -= report_font->height;
	}
}

static inline bool height_needs_to_increase(Console* console)
{
	return console->current_render_height_fraction < console->desired_render_height_fraction;
}

static inline bool height_needs_to_decrease(Console* console)
{
	return console->current_render_height_fraction > console->desired_render_height_fraction;
}

static void update_height(Console* console)
{
	static float render_height_fraction_change = 0.016667f * console->render_height_fraction_delta;

	if (height_needs_to_increase(console)) {
		console->current_render_height_fraction += render_height_fraction_change;	
		if (height_needs_to_decrease(console)) {
			console->current_render_height_fraction = console->desired_render_height_fraction;		
		}
	} else if (height_needs_to_decrease(console)) {
		console->current_render_height_fraction -= render_height_fraction_change;		
		if (console->current_render_height_fraction < 0.0f) {
			console->current_render_height_fraction = 0.0f;		
		}
	} else {
		return;		
	}
}

void console_set_state(Console* console, CONSOLE_STATE console_state)
{
	// possible add x-macros
	if (console_state == OPEN_SMALL) {
		console->desired_render_height_fraction = 0.25f;	
	} else if (console_state == OPEN_LARGE) {
		console->desired_render_height_fraction = 0.75f;
	} else if (console_state == CLOSED) {
		console->desired_render_height_fraction = 0.0f;
	} else {
		return;
	}
}

bool console_is_open(Console* console)
{
	return console->current_render_height_fraction > 0.0f;		
}

#define lerp(val1, val2, percentange) \
	((val1) + (percentage) * (((val2)) - (val1)))
static int get_current_height(Console* console, I_Renderer* renderer)
{
	return console->current_render_height_fraction * renderer->logical_height;
}

// ----------------------------------------------------------------------------

typedef struct {
	const char* string;
	bool entered;
	bool escaped;
	uint8_t input_buffer[8000];
} TextInput;
// TTF_RenderUTF8_Blended

const char text[8000]; // markedtext ???
const int cursor = 0;
SDL_Rect text_rect, marked_rect;

void init_input()
{
	text_rect = {
		.x = 100,
		.y = 100,
		.w = 300,
		.h = 50
	};
	marked_rect = text_rect;

	text[0] = 0;
	marked_text[0] = 0;

	SDL_StartTextInput(); // so we can capture events. SDL_StopTextInput()
}

void draw()
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	
	// draw input area
	SDL_RenderFillRect(renderer, &text_rect);

	// draw recieved text
	SDL_Surface* input_text_surface = TTF_RenderUTF8_Blended(font, text, colour);
	SDL_Texture* input_text_texture = SDL_CreateTextureFromSurface(renderer, input_text_surface);
	SDL_Rect input_text = {
		.x = text_rect.x,
		.y = text_rect.y,
		.w = input_text_surface->w,
		.h = input_text_surface->h
	};
	SDL_RenderCopy(renderer, input_text_texture, NULL, &input_text);

	int input_text_width;
	int input_text_height;
	TTF_SizeUTF8(font, text, &input_text_width, &input_text_height);
}

size_t utf8_char_block_length(char* ch)
{
	const char GET_2_MSB_MASK = 0xc0;
	const char SINGLE_BLOCK_INDICATOR = 0x80;

	for (size_t char_index = 0, block_count = 0; ch[char_index] != '\0'; ++char_index) {
		if (ch[char_index] & GET_2_MSB_MASK != SINGLE_BLOCK_INDICATOR) {
			++block_count;		
		} 
	}

	return block_count;
}

char* utf8_char_next(char* ch)
{
	size_t block_length = utf8_char_block_length(ch);	

	if (block_length == 0) {
		return 0;
	} else {
		for (size_t block_index = 0; block_index < block_length; ++block_index) {
			++ch;			
		}		
	}

	return ch;
}

char* utf8_char_advance(char* ch, size_t delta)
{
	for (size_t utf8_char_index = 0; utf8_char_index < delta && ch[utf8_char_index] != '\0'; ++utf8_char_index) {
		ch = utf8_next_char(ch);
	}

	return ch;
}

// ----------------------------------------------------------------------------

#endif

int main(void)
{
	case SDLK_F1:
		if (console_is_open(console)) { // toggling
			console_set_state(console, CLOSED); // console_render(console)
		} else {
			console_set_state(console, OPEN_LARGE);
		}
}

void render(void)
{
	console_render();
}

// handle_global_events(SDL_Event* event) 
void events(SDL_Event* event)
{
	switch (event->type) {
	case SDL_TEXTINPUT:
		const char* text = event->text.text;
	case SDL_TEXTEDITING:
	case SDLK_UP:
		// control cursor position
	}
}
