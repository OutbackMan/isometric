#ifndef __console_h__
#define __console_h__

TTF_Font* input_font;
TTF_Font* report_font;

SDL_Colour input_bg_colour;
SDL_Colour input_text_colour;
SDL_Colour report_bg_colour;
SDL_Colour report_text_colour;

// want going from all the way across the screen
float window_x0 = 0.0f; 
float window_y0 = 1.0f;
float window_y_b = 0.70f; // maximum distance allowed down the screen

typedef enum {
	CONSOLE_CLOSED,
	CONSOLE_OPEN_SMALL,
	CONSOLE_OPEN_BIG
} STATE; // extent

float openness_max = 0.7f; // fraction of screen space

float current_open_size = 0.0f; // open_t
float desired_open_size = 0.0f; // open_t_target
float open_size_rate = 7.0f; // dopen_dt

void draw()
{
	update_openness();	

	float x0 = window_x0 * window_width;	
	float x1 = window_x1 * window_width;	

	float y0 = get_bottom();
	float y1 = window_height;	

	float input_y0 = y0;
	y0 += input_font->height;

	cursor_in_output = false;

	draw_rect(x0, input_y0, x1, y1, input_bg_colour); // input
	draw_rect(x0, y0, x1, y1, report_bg_colour); // output
	x0 += 4; // padding


}

void update_openness()
{
	float open_size_delta = 0.016667 * open_size_rate;

	if (current_open_size < desired_open_size) {
		current_open_size += open_size_delta;	
		if (current_open_size > desired_open_size) {
			current_open_size = desired_open_size;		
		}
	} else if (current_open_size > desired_open_size) {
		current_open_size -= open_size_delta;		
		if (current_open_size < 0) {
			current_open_size = 0;		
		}
	} else {
		return;		
	}
}

void open_or_close(STATE state)
{
	it (state == CONSOLE_OPEN_SMALL) {
		desired_open_size = 1.0f;	
	} else if (state == CONSOLE_OPEN_LARGE) {
		desired_open_size = 3.0f;
	} else if (state == CONSOLE_CLOSED) {
		desired_open_size = 0.0f;
	} else {
		return;		
	}
}

bool is_open()
{
	return current_open_size > 0.0f;		
}

float get_bottom()
{
	return lerp(1.0f,	
}

#endif
