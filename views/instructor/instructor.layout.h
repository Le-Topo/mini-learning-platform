#ifndef INSTRUCTOR_LAYOUT_H
#define INSTRUCTOR_LAYOUT_H

#include <curses.h>
#include "../../utils/curses/curses-utilities.h"
#include "../../routes/routes.h"
#include "../../utils/session-handler/session-handler.h"

#define INSTRUCTOR_SIDEBAR_WIDTH 30
#define INSTRUCTOR_SIDEBAR_HEIGHT 20

#define INSTRUCTOR_SIDEBAR_START_X 2
#define INSTRUCTOR_SIDEBAR_START_Y 1

#define INSTRUCTOR_SIDEBAR_ITEMS_COUNT 6

#define FREE_SPACE_START_X (INSTRUCTOR_SIDEBAR_WIDTH + INSTRUCTOR_SIDEBAR_START_X + 4)
#define FREE_SPACE_START_Y (INSTRUCTOR_SIDEBAR_START_Y + 6)

typedef enum InstructorSidebarItem {
    INSTRUCTOR_DASHBOARD = 0,
    INSTRUCTOR_COURSES = 1,
    INSTRUCTOR_NEW_COURSE = 2,
    INSTRUCTOR_NOTIFICATIONS = 3,
    INSTRUCTOR_SETTINGS = 4,
    INSTRUCTOR_LOGOUT = 5,
} InstructorSidebarItem;

void render_instructor_sidebar(WINDOW *win, InstructorSidebarItem selected_item);

char* get_instructor_sidebar_item_name(InstructorSidebarItem item);

char** get_instructor_sidebar_items();

Route get_instructor_page_route_from_key(int pressed_key);

bool can_handle_pressed_key_in_sidebar(int pressed_key);

#endif //INSTRUCTOR_LAYOUT_H
