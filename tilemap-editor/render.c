#include "render.h"

#include "events.h" // this a program wide event handler which is populated with mouse position, key presses, etc.

void editor_draw_tile(int x0, int y0, unsigned tile_id, EDITOR_DRAW_MODE draw_mode, float* tile_data);
