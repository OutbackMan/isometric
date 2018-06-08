int main(void)
{
	while (running) {
		while (events) {
			events();		
		}		
		update();
		render();
	}	
}

void events()
{
	
}

void update()
{
	
}

void render()
{
	
}

// START(button)
typedef struct {
	int x0, y0;
	int width, height;
	bool mouse_is_over;
	bool mouse_has_clicked;
} Button;

button_create()
{
}

button_events()
{
	case SDL_MOUSEMOTION:
	if (mouse.x >= button->x0 && mouse.x <= button->width && 
		mouse.y >= button->y0 && mouse.y <= button->height) {
		button->mouse_is_over = true;
	} else {
		button->mouse_is_over = false;
	}
	case SDL_MOUSEBUTTONDOWN:
	if (button->mouse_is_over) {
		button->mouse_has_clicked = true;		
	} else {
		button->mouse_has_clicked = false;		
	}
	
}


button_update()
{
	
}

button_render()
{
	if (button->mouse_is_over) {
		// specific		
	}
}

// END(button)

// START(ui)
enum {
	STATE_ACTIVE,
	STATE_FREEZE
};

typedef struct {
	STRETCHY_BUF(Button*) buttons;	
} UI;

ui_create() {
	BUF_PUSH(ui->buttons, button_create("load button"));
	BUF_PUSH(ui->buttons, button_create("save button"));
	BUF_PUSH(ui->buttons, button_create("another button"));
}

ui_render() {
	for (size_t button_index = 0; button_index < BUTTON__NUM; ++button_index) {
		button_draw(ui->buttons[button_index]);		
	}
}
// END(ui)

// START(map)
typedef struct {
	int* tiles;
	int render_tile_width;
	int render_tile_height;
	int num_tile_width;
} Map;

map_set_tile()
{
	case MOUSE_BUTTONDOWN:	
	int mouse_map_x = mouse.x / map->tile_width + draw_offset_x;
	int mouse_map_y = mouse.y / map->tile_height + draw_offset_y;
	if (mouse_map_x < map_width && mouse_map_y < map_height) {
		map->tiles[mouse_map_x][mouse_map_y] = tile_id;		
	}
}

map_events() {
	if (event.key.keysym.sym == SDLK_left) {
		if (map->draw_offset_x < map->map_width - 1) {
			map->draw_offset_x += 1; // think in relation to what tile you were already on, i.e, its index is now plus 1
		}		
	} else if (event.key.keysym.sym == SDLK_right) {
		if (map->draw_offset_x > 0) {
			map->draw_offset_x -= 1;		
		}		
	} else if (event.key.keysym.sym == SDLK_up) {
		if (map->draw_offset_y < map->map_height - 1) {
			map->draw_offset_x += 1;	
		}		
	}
}

map_render()
{
	for (size_t map_x = 0; map_x < map->map_width; ++map_x) {
		for (size_t map_y = 0; map_y < map->map_height; ++map_y) {
			if (map->tiles[map_y][map_x] != EMPTY) {
				tile_render((x - draw_offset_x) * tile_width, (y - draw_offset_y) * tile_height);		
			}		
		}	
	}	
}

map_save()
map_load() // load data into tiles*
// END(map)





