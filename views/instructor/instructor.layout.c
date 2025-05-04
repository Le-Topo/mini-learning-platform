#include "./instructor.layout.h"

static char *sidebar_items[] = {
    "Tableau de bord",
    "Mes cours",
    "Nouveau cours",
    "Notifications",
    "Parametres",
    "Se deconnecter"
};

void render_instructor_sidebar(WINDOW *win, InstructorSidebarItem selected_item) {
    int i;

    wattron(win, A_BOLD);
    mvwprintw(win, 2, INSTRUCTOR_SIDEBAR_START_X + (INSTRUCTOR_SIDEBAR_WIDTH - 5)/2, "Mini");
    mvwprintw(win, 3, INSTRUCTOR_SIDEBAR_START_X + (INSTRUCTOR_SIDEBAR_WIDTH - 17)/2, "Learning Platform");
    wattroff(win, A_BOLD);


    draw_rectangle(win, INSTRUCTOR_SIDEBAR_START_X, INSTRUCTOR_SIDEBAR_START_Y, INSTRUCTOR_SIDEBAR_WIDTH, 3);
    draw_rectangle(win, 2, 4, INSTRUCTOR_SIDEBAR_WIDTH, INSTRUCTOR_SIDEBAR_HEIGHT);

    for (i = 0; i < INSTRUCTOR_SIDEBAR_ITEMS_COUNT; i++) {
        if (i == selected_item) {
            wattron(win, A_REVERSE);
            wattron(win, COLOR_PAIR(3));
        }

        if (i == INSTRUCTOR_LOGOUT) {
          wattron(win, COLOR_PAIR(1));
        }

        int itemY = i * 2 + INSTRUCTOR_SIDEBAR_START_Y + 5;
        mvwprintw(win, itemY, 5, "[F%d] %s", i+1, sidebar_items[i]);

        if (i == INSTRUCTOR_NOTIFICATIONS) {
            mvwprintw(win, itemY, INSTRUCTOR_SIDEBAR_WIDTH - 3, "(1)");
        }

        if (i == selected_item) {
            wattroff(win, A_REVERSE);
            wattroff(win, COLOR_PAIR(3));
        }

        if (i == INSTRUCTOR_LOGOUT) {
            wattroff(win, COLOR_PAIR(1));
        }
        mvhline(itemY+1, 5, 0, INSTRUCTOR_SIDEBAR_WIDTH - 6);
    }

    char *pageTitle = get_instructor_sidebar_item_name(selected_item);
    wattron(win, A_BOLD);
    mvwprintw(win, 2, (INSTRUCTOR_SIDEBAR_WIDTH + INSTRUCTOR_SIDEBAR_START_X + 4 + MAX_WIN_COLS - strlen(pageTitle))/2, "%s", pageTitle);
    wattroff(win, A_BOLD);

    mvwhline(win, 4, INSTRUCTOR_SIDEBAR_WIDTH + INSTRUCTOR_SIDEBAR_START_X + 4, 0, MAX_WIN_COLS - INSTRUCTOR_SIDEBAR_WIDTH - INSTRUCTOR_SIDEBAR_START_X);

    User user = get_session_user();
    char greetings[60];
    snprintf(greetings, sizeof(greetings), "Bonjour, %s !", user.firstname);
    mvhline(INSTRUCTOR_SIDEBAR_HEIGHT + INSTRUCTOR_SIDEBAR_START_Y+1, INSTRUCTOR_SIDEBAR_START_X, '-', INSTRUCTOR_SIDEBAR_WIDTH + INSTRUCTOR_SIDEBAR_START_X-1);

    mvwprintw(win, INSTRUCTOR_SIDEBAR_HEIGHT + INSTRUCTOR_SIDEBAR_START_Y+2, 5, "%s", greetings);

    wrefresh(win);
}

char* get_instructor_sidebar_item_name(InstructorSidebarItem item) {
    return sidebar_items[item];
}

char** get_instructor_sidebar_items() {
    return sidebar_items;
}

Route get_instructor_page_route_from_key(int pressed_key)
{
  if (!can_handle_pressed_key_in_sidebar(pressed_key)) {
    return ROUTE_EXIT;
  }

  const InstructorSidebarItem selectedItem = (InstructorSidebarItem)(pressed_key - KEY_F(1));

  switch (selectedItem) {
    case INSTRUCTOR_DASHBOARD:
      return ROUTE_INSTRUCTOR_DASHBOARD;
    case INSTRUCTOR_COURSES:
      return ROUTE_INSTRUCTOR_COURSES;
    case INSTRUCTOR_NEW_COURSE:
      return ROUTE_INSTRUCTOR_NEW_COURSE;
    case INSTRUCTOR_NOTIFICATIONS:
      return ROUTE_INSTRUCTOR_NOTIFICATIONS;
    case INSTRUCTOR_SETTINGS:
      return ROUTE_INSTRUCTOR_SETTINGS;
    case INSTRUCTOR_LOGOUT:
      return ROUTE_LOGOUT;
    default:
      return ROUTE_EXIT;
  }
}

bool can_handle_pressed_key_in_sidebar(int pressed_key) {
    return (pressed_key >= KEY_F(1) && pressed_key <= KEY_F(INSTRUCTOR_SIDEBAR_ITEMS_COUNT));
}