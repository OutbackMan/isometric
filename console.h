#ifndef __console_h__
#define __console_h__

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

	float max_render_height_fraction;	
	float current_render_height_fraction = 0.0f; // open_t
	float desired_render_height_fraction = 0.0f; // open_t_target
	float render_height_delta = 1.0f; // dopen_dt

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

	console->max_render_height_fraction = 0.7f;
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

	const SDL_Rect input_render_rect = {
		.x = 0,
		.y = 0,
		.w = window_width,
		.h = get_current_height()
	};
	SDL_RenderSetDrawColor(renderer, console->input_bg_colour->r); // ... create wrapper
	SDL_RenderFillRect(renderer, &input_render_rect);

	const SDL_Rect report_render_rect = {
		.x = 0,
		.y = get_bottom(),
		.w = window_width,
		.h = get_bottom() + console->report_font->height
	};
	SDL_RenderSetDrawColor();
	SDL_RenderFillRect(renderer, &report_render_rect);
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
	static float open_size_delta = 0.016667 * console->open_size_rate;

	if (height_needs_to_increase(console)) {
		console->current_render_height_fraction += open_size_delta;	
		if (height_needs_to_decrease(console)) {
			console->current_render_height_fraction = console->desired_render_height_fraction;		
		}
	} else if (height_needs_to_decrease(console)) {
		console->current_render_height_fraction -= open_size_delta;		
		if (console->current_render_height_fraction < 0) {
			console->current_render_height_fraction = 0;		
		}
	} else {
		return;		
	}
}

void console_set_state(Console* console, CONSOLE_STATE console_state)
{
	it (console_state == OPEN_SMALL) {
		console->desired_render_height_fraction = 1.0f;	
	} else if (console_state == OPEN_LARGE) {
		console->desired_render_height_fraction = 3.0f;
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

static float get_current_height(Console* console)
{
	return lerp(
			1.0f, 
			console->max_render_height_fraction, 
			console->current_render_height_fraction
		) * window_height;
}

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
	console_render(); // always have this
}
