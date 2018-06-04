#ifndef __widget_panels_h__
#define __widget_panels_h__

#include "widget-info.h"

/* use this pattern when only a single instance is required/logical */

enum {
	EDITOR_WIDGET_PANEL_TOOLBAR,
	EDITOR_WIDGET_PANEL_COLORPIck,
	EDITOR_WIDGET_PANEL_INFO,
	EDITOR_WIDGET_PANEL_LAYERS,
	EDITOR_WIDGET_PANEL_PROPS,
	EDITOR_WIDGET_PANEL_CATEGORIES,
	EDITOR_WIDGET_PANEL_TILES,

	EDITOR_WIDGET_PANEL__NUM
};

typedef struct {
	bool is_expanded, 
	int mode;
	int delta_height;
	EDITOR_WIDGET_INFO_SIDE side;
	int width,height;
	int x0,y0;	
} EditorWidgetPanel;


#endif
