//
// Created by astri on 2025-04-26.
//

#ifndef LEARNER_LAYOUT_H
#define LEARNER_LAYOUT_H

#include <curses.h>
#include "../../utils/curses/curses-utilities.h"
#include "../../routes/routes.h"
#include "../../utils/session-handler/session-handler.h"

#define LEARNER_SIDEBAR_WIDTH 30
#define LEARNER_SIDEBAR_HEIGHT 20

#define LEARNER_SIDEBAR_START_X 2
#define LEARNER_SIDEBAR_START_Y 1

#define LEARNER_SIDEBAR_ITEMS_COUNT 6

#define LEARNER_FREE_SPACE_START_X (LEARNER_SIDEBAR_WIDTH + LEARNER_SIDEBAR_START_X + 4)
#define LEARNER_FREE_SPACE_START_Y (LEARNER_SIDEBAR_START_Y + 6)

typedef enum LearnerSidebarItem {
    LEARNER_DASHBOARD = 0,
    LEARNER_COURSES = 1,
    LEARNER_TAKEN_COURSES = 2,
    LEARNER_NOTIFICATIONS = 3,
    LEARNER_SETTINGS = 4,
    LEARNER_LOGOUT = 5,
} LearnerSidebarItem;

void render_learner_sidebar(WINDOW *win, LearnerSidebarItem selected_item);

char* get_learner_sidebar_item_name(LearnerSidebarItem item);

char** get_learner_sidebar_items();

Route get_learner_page_route_from_key(int pressed_key);

bool can_handle_pressed_key_in_learner_sidebar(int pressed_key);

void change_page_title(WINDOW *win, const char *title);

#endif //LEARNER_LAYOUT_H
