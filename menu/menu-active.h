#ifndef __menu_menu_active_h__
#define __menu_menu_active_h__

typedef enum {
	MENU_PAGE_MAIN,
	MENU_PAGE_CONTROLS
} I_MENU_PAGE_ID;

void i_menu_active_set(I_MENU_PAGE_ID active_menu_page_id);

I_MENU_PAGE_ID i_menu_active_get(void);

#endif

#include "menu/menu-active.h"

static struct {
	I_MENU_PAGE_ID active_menu_page_id;		
} __MENU_ACTIVE;

void i_menu_active_set(I_MENU_PAGE_ID active_menu_page_id)
{
	__MENU_ACTIVE.active_menu_page_id = active_menu_page_id;
}

I_MENU_PAGE_ID i_menu_active_get(void)
{
	return __MENU_ACTIVE.active_menu_page_id;
}
