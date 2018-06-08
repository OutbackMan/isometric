#ifndef __ui_h__
#define __ui_h__

enum {
	EDITOR_UI_REGION_LEFT,
	EDITOR_UI_REGION_TOP,
	EDITOR_UI_REGION_RIGHT,
	EDITOR_UI_REGION_BOTTOM,

	EDITOR_UI_REGION__NUM
};


enum {
	EDITOR_UI_REGION_LEFT,
	EDITOR_UI_REGION_TOP,
	EDITOR_UI_REGION_RIGHT,
	EDITOR_UI_REGION_BOTTOM,

	EDITOR_UI_REGION__NUM
};

typedef struct {
	int x0;
	int y0;
	int width;
	int height;
	bool is_active;
	float retracted;
} EditorUI__Region;

typedef struct {
	int x0;
	int y0;
	int width;
	int height;
	bool is_expanded;
	int delta_height;
} EditorUI__Panel;

typedef struct {
	EditorUI__Region regions[EDITOR_UI_REGION__NUM];	
	EditorUI__Panel panels[EDITOR_UI_PANEL__NUM];
} EditorUI;



#endif
