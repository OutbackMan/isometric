/*
 scaling/zooming -> stbte_set_spacing()
 each tile has properties and can be linked
*/

typedef struct {

} Tilemap; // stbte_tilemap;

typedef struct {
 short x,y;
} Link; // stbte__link

enum {
  DRAWMODE_DEEMPHASISE = -1
  DRAWMODE_EMPHASISE,
  DRAWMODE_NORMAL
}; // STBTE_drawmode_deemphasize;

enum {
  PROPERTY_NONE,
  PROPERTY_INT,
  PROPERTY_FLOAT,
  PROPERTY_BOOL,
  PROPERTY_DISABLED
}; // STBTE_PROP_none;

enum {
  ACTION_TOOL_SELECT,
  ACTION_TOOL_BRUSH
}; // STBTE_tool_select;

#define NOTUSED(v) (void)(v)

enum {
 COLOUR_GROUP_TOOLBAR_BUTTON,
 COLOUR_GROUP_LAYER_BUTTON,
 COLOUR_GROUPS__NUM 
}; // STBTE__ctoolbar_button (mode)

enum {
 COLOUR_ACTION_OVER,
 COLOUR_ACTION_DOWN,
 COLOUR_ACTION__NUM
}; // STBTE__idle (state)

enum {
 COLOUR_VARIANT_BASE,
 COLOUR_VARIANT_TEXT,
 COLOUR_VARIANT__NUM
}; // STBTE__base (aspect)

// stbte__color_names[]
static char* colour_group_names[] = { "toolbar button", "layer" };

SDL_Colour colour_table = {
 [COLOUR_GROUP_TOOLBAR_BUTTON] = {
  [COLOUR_ACTION_OVER] = {
   [COLOUR_VARIANT_BASE] = { 255, 255, 255, 255 },
   [COLOUR_VARIANT_TEXT] = { 125, 125, 125, 255 }
  }
 }
};

// fontdata[] = {} ???
