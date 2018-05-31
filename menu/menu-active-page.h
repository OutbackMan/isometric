#ifndef __menu_menu_active_page_h__
#define __menu_menu_active_page_h__

typedef enum {
	MENU_PAGE_MAIN,
	MENU_PAGE_CONTROLS
} I_MENU_PAGE_ID;

void i_menu_active_page_set(I_MENU_PAGE_ID active_menu_page);

I_MENU_PAGE_ID i_menu_active_page_get(void);

#endif

