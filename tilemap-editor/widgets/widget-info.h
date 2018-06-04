#ifndef __widget_info_h__
#define __widget_info_h__

enum {
   EDITOR_WIDGET_COLOR_VARIANT_BASE,
   EDITOR_WIDGET_COLOR_VARIANT_OUTLINE,
   EDITOR_WIDGET_COLOR_VARIANT_TEXT,

   EDITOR_WIDGET_COLOR_VARIANT__NUM
};

enum {
   EDITOR_WIDGET_COLOR_STATE_IDLE,
   EDITOR_WIDGET_COLOR_STATE_OVER,
   EDITOR_WIDGET_COLOR_STATE_DOWN,
   EDITOR_WIDGET_COLOR_STATE_OVER_DOWN,
   EDITOR_WIDGET_COLOR_STATE_SELECTED,
   EDITOR_WIDGET_COLOR_STATE_SELECTED_OVER,
   EDITOR_WIDGET_COLOR_STATE_DISABLED,

   EDITOR_WIDGET_COLOR_STATE__NUM
};

typedef enum {
	POSITION_LEFT,
	POSITION_RIGHT,
	POSITION_TOP,
	POSITION_BOTTOM
} EDITOR_WIDGET_INFO_POSITION;


#endif
