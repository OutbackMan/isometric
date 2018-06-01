/*
 scaling/zooming -> stbte_set_spacing()
 each tile has properties and can be linked
*/

typedef struct {

} Tilemap; // stbte_tilemap;

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

