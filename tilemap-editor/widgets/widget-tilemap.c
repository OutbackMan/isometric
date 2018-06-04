#include "widget-tilemap.h"

#include "widget-colors.h"

EditorWidgetTileMap* widget_tilemap_create(int max_x, int max_y, int layers, int spacing_x, int spacing_y)
{
	EditorWidgetTileMap* tile_map = xmalloc(sizeof(EditorWidgetTileMap));
		
	if (max_x < 0 || max_y < 0 || layers < 0);

	// for multidimensional arrays: arr[HEIGHT][WIDTH] (iterate with y as outer loop)
	// i = y * w + x
	// i = x + h * (y + w * z)

	return tile_map;
}
