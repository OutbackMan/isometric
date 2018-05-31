#include "menu/menu-active-page.h"

static struct {
	I_MENU_PAGE_ID active_menu_page;
} __MENU_ACTIVE;

void i_menu_active_page_set(I_MENU_PAGE_ID active_menu_page)
{
	__MENU_ACTIVE_PAGE.active_menu_page = active_menu_page;
}

I_MENU_PAGE_ID i_menu_active_page_get(void)
{
	return __MENU_ACTIVE_PAGE.active_menu_page;
}
