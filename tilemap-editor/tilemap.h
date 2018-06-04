#ifndef __widget_tilemap_h__
#define __widget_tilemap_h__

enum {
	EDITOR_WIDGET_TILEMAP_COLOR_BACKGROUND,
	EDITOR_WIDGET_TILEMAP_COLOR_BORDER,         
	EDITOR_WIDGET_TILEMAP_COLOR_HIGHLIGHT,
	EDITOR_WIDGET_TILEMAP_COLOR_GRID,               
	EDITOR_WIDGET_TILEMAP_COLOR_SELECTION_OUTLINE1,
	EDITOR_WIDGET_TILEMAP_COLOR_SELECTION_OUTLINE2,
	EDITOR_WIDGET_TILEMAP_COLOR_TILEPALETTE_OUTLINE,
	EDITOR_WIDGET_TILEMAP_COLOR_TILEPALETTE_BACKGROUND,

	EDITOR_WIDGET_TILEMAP_COLOUR__NUM,
};

typedef enum {
	TILE_PROPERTY_NONE,
	TILE_PROPERTY_INT,
	TILE_PROPERTY_FLOAT,
	TILE_PROPERTY_BOOL,
	TILE_PROPERTY_DISABLED
} EDITOR_WIDGET_TILEMAP__TILE_PROPERTY;

typedef struct {
	int x;
	int y;
} EditorWidgetTilemap__Link;

typedef struct {
	int id;
	unsigned category_id;
	char* category;
	unsigned layer_mask;
} EditorWidgetTilemap__TileInfo;





typedef struct {
	int tile_data[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH][EDITOR_LAYERS_MAX];
	float tile_properties[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH][EDITOR_PROPERTIES_MAX];
	Tilemap__Link tile_links[EDITOR_TILEMAP_MAX_HEIGHT][EDITOR_TILEMAP_MAX_WIDTH];
	unsigned layers_in_use;
	unsigned tile_render_width;
	unsigned tile_render_height;
	int current_category, current_tile, current_layer;
	const char* categories[EDITOR_CATEGORIES_MAX];
	int num_categories, category_scroll;
	WidgetTilemap__TileInfo* tiles;
	int num_tiles, max_tiles, digits;
	bool valid_undo_is_available;
	bool undo_is_available;
	bool redo_is_available;
	unsigned char padding;
	int cur_palette_count;
	int palette_scroll;
	int tileinfo_dirty;
	WidgetTilemap__Layer layer_info[EDITOR_LAYERS_MAX];
	int has_layer_names;
	int layername_width;
	int layer_scroll;
	int property_mode;
	int solo_layer;
	int undo_pos, undo_len, redo_len;
	short background_tile;
	unsigned char id_in_use[32768 >> 3];
	short undo_buffer[BUFFER_MAX];
} EditorWidgetTilemap;

#endif
