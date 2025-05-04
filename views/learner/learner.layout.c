#include "./learner.layout.h"

static char *sidebar_items[] = {
    "Tableau de bord",
    "Cours disponibles",
    "Mes cours suivis",
    "Notifications",
    "Parametres",
    "Se deconnecter"
};

void render_learner_sidebar(WINDOW *win, LearnerSidebarItem selected_item) {
    int i;

    wattron(win, A_BOLD);
    mvwprintw(win, 2, LEARNER_SIDEBAR_START_X + (LEARNER_SIDEBAR_WIDTH - 5)/2, "Mini");
    mvwprintw(win, 3, LEARNER_SIDEBAR_START_X + (LEARNER_SIDEBAR_WIDTH - 17)/2, "Learning Platform");
    wattroff(win, A_BOLD);


    draw_rectangle(win, LEARNER_SIDEBAR_START_X, LEARNER_SIDEBAR_START_Y, LEARNER_SIDEBAR_WIDTH, 3);
    draw_rectangle(win, 2, 4, LEARNER_SIDEBAR_WIDTH, LEARNER_SIDEBAR_HEIGHT);

    for (i = 0; i < LEARNER_SIDEBAR_ITEMS_COUNT; i++) {
        if (i == selected_item) {
            wattron(win, A_REVERSE);
            wattron(win, COLOR_PAIR(3));
        }

        if (i == LEARNER_LOGOUT) {
          wattron(win, COLOR_PAIR(1));
        }

        int itemY = i * 2 + LEARNER_SIDEBAR_START_Y + 5;
        mvwprintw(win, itemY, 5, "[F%d] %s", i+1, sidebar_items[i]);

        if (i == LEARNER_NOTIFICATIONS) {
            mvwprintw(win, itemY, LEARNER_SIDEBAR_WIDTH - 3, "(0)");
        }

        if (i == selected_item) {
            wattroff(win, A_REVERSE);
            wattroff(win, COLOR_PAIR(3));
        }

        if (i == LEARNER_LOGOUT) {
            wattroff(win, COLOR_PAIR(1));
        }
        mvhline(itemY+1, 5, 0, LEARNER_SIDEBAR_WIDTH - 6);
    }

    char *pageTitle = get_learner_sidebar_item_name(selected_item);
    wattron(win, A_BOLD);
    mvwprintw(win, 2, (LEARNER_SIDEBAR_WIDTH + LEARNER_SIDEBAR_START_X + 4 + MAX_WIN_COLS - strlen(pageTitle))/2, "%s", pageTitle);
    wattroff(win, A_BOLD);

    mvwhline(win, 4, LEARNER_SIDEBAR_WIDTH + LEARNER_SIDEBAR_START_X + 4, 0, MAX_WIN_COLS - LEARNER_SIDEBAR_WIDTH - LEARNER_SIDEBAR_START_X);

    User user = get_session_user();
    char greetings[60];
    snprintf(greetings, sizeof(greetings), "Bonjour, %s !", user.firstname);
    mvhline(LEARNER_SIDEBAR_HEIGHT + LEARNER_SIDEBAR_START_Y+1, LEARNER_SIDEBAR_START_X, '-', LEARNER_SIDEBAR_WIDTH + LEARNER_SIDEBAR_START_X-1);

    mvwprintw(win, LEARNER_SIDEBAR_HEIGHT + LEARNER_SIDEBAR_START_Y+2, 5, "%s", greetings);

    wrefresh(win);
}

char* get_learner_sidebar_item_name(LearnerSidebarItem item) {
    return sidebar_items[item];
}

char** get_learner_sidebar_items() {
    return sidebar_items;
}

Route get_learner_page_route_from_key(int pressed_key)
{
  if (!can_handle_pressed_key_in_learner_sidebar(pressed_key)) {
    return ROUTE_EXIT;
  }

  const LearnerSidebarItem selectedItem = (LearnerSidebarItem)(pressed_key - KEY_F(1));

  switch (selectedItem) {
    case LEARNER_DASHBOARD:
      return ROUTE_LEARNER_DASHBOARD;
    case LEARNER_COURSES:
      return ROUTE_LEARNER_COURSES;
    case LEARNER_TAKEN_COURSES:
      return ROUTE_LEARNER_TAKEN_COURSES;
    case LEARNER_NOTIFICATIONS:
      return ROUTE_LEARNER_NOTIFICATIONS;
    case LEARNER_SETTINGS:
      return ROUTE_LEARNER_SETTINGS;
    case LEARNER_LOGOUT:
      return ROUTE_LOGOUT;
    default:
      return ROUTE_EXIT;
  }
}

bool can_handle_pressed_key_in_learner_sidebar(int pressed_key) {
    return (pressed_key >= KEY_F(1) && pressed_key <= KEY_F(LEARNER_SIDEBAR_ITEMS_COUNT));
}

void change_page_title(WINDOW *win, const char *title) {
    int titleX = (LEARNER_SIDEBAR_WIDTH + LEARNER_SIDEBAR_START_X + 4 + MAX_WIN_COLS - strlen(title))/2;
    mvwprintw(win, 2, LEARNER_FREE_SPACE_START_X, "%s", LONG_BLANK_LINE);
    mvwprintw(win, 2, LEARNER_FREE_SPACE_START_X+30, "%s", LONG_BLANK_LINE);
    wattron(win, A_BOLD);
    mvwprintw(win, 2, titleX, "%s", title);
    wattroff(win, A_BOLD);
}
