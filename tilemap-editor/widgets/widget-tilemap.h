#ifndef __widget_tilemap_h__
#define __widget_tilemap_h__

typedef struct {
	short data[EDITOR_WIDGET_TILEMAP_MAX_Y][EDITOR_WIDGET_TILEMAP_MAX_X][EDITOR_MAX_LAYERS];
	float properties[EDITOR_WIDGET_TILEMAP_MAX_Y][EDITOR_WIDGET_TILEMAP_MAX_X][EDITOR_MAX_PROPERTIES];
	WidgetTilemap__Link links[EDITOR_WIDGET_TILEMAP_MAX_Y][EDITOR_WIDGET_TILEMAP_MAX_X];
	int link_counts[EDITOR_WIDGET_TILEMAP_MAX_Y][EDITOR_WIDGET_TILEMAP_MAX_X];
	int max_x, max_y, num_layers;
	int spacing_x, spacing_y;
	int palette_spacing_x, palette_spacing_y;
	int scroll_x, scroll_y;
	int current_category, current_tile, current_layer;
	char* categories[MAX_CATEGORIES];
	int num_categories, category_scroll;
	WidgetTilemap__TileInfo* tiles;
	int num_tiles, max_tiles, digits;
	unsigned char undo_available_valid;
	unsigned char undo_available;
	unsigned char redo_available;
	unsigned char padding;
	int cur_palette_count;
	int palette_scroll;
	int tileinfo_dirty;
	WidgetTilemap__Layer layer_info[MAX_LAYERS];
	int has_layer_names;
	int layername_width;
	int layer_scroll;
	int property_mode;
	int solo_layer;
	int undo_pos, undo_len, redo_len;
	short background_tile;
	unsigned char id_in_use[32768 >> 3];
	short* undo_buffer;
} WidgetTilemap;

#endif
