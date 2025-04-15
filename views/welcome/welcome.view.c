//
// Created by astri on 2025-04-11.
//
#include "welcome.view.h"

#define TABS_NUMBER 3

Route render_welcome_view()
{
  WINDOW *welcomeWindow = newwin(MAX_WIN_LINES, MAX_WIN_COLS, 0, 0);
  int ctrl = 0;
  const char *pageTitle = "Bienvenue sur Mini Leanrning Platform !";
  char **tabs = malloc(sizeof(char *) * TABS_NUMBER);
  tabs[0] = "Apprenant";
  tabs[1] = "Instructeur";
  tabs[2] = "Administrateur";
  bool hasFocus = false;
  char *currentQuote = "";
  bool shouldClearScreen = false;

  Route nextRoute = EXIT;

  int currentTab = 2;

  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int i = 1;
  while (ctrl != KEY_F(1)) {
    if (ctrl == 410) {
      ctrl = '\0';
      continue;
    }
    // if (shouldClearScreen) {
    //   // wclear(welcomeWindow);
    //   box(welcomeWindow, 0, 0);
    //   shouldClearScreen = false;
    // }

    wattron(welcomeWindow, COLOR_PAIR(5));
    mvwprintw(welcomeWindow, MAX_WIN_LINES-2, 2, "Utiliser la touche TAB pour naviguer entre les onglets et la touche F1 pour quitter");
    wattroff(welcomeWindow, COLOR_PAIR(5));

    print_in_hmiddle_of_window(welcomeWindow, 2, MAX_WIN_COLS, pageTitle);

    int tabX = 34;
    int tabY = 5;
    for (int i = 0; i < TABS_NUMBER; i++) {
      if (i == currentTab) {
          wattron(welcomeWindow, COLOR_PAIR(4));
      }

      draw_rectangle_with_text(welcomeWindow, &tabX, &tabY, tabs[i], 6, 1, false, MAX_WIN_COLS);
      tabY -= 2;

      if (i == currentTab) {
          wattroff(welcomeWindow, COLOR_PAIR(4));
      }
    }

    draw_rectangle(welcomeWindow, 30, 8, tabX-26, 16);

    switch(get_user_role_from_tab(currentTab)) {
      case ADMIN:
        mvwprintw(welcomeWindow, 11, 34, "[1] Se connecter");
        mvwprintw(welcomeWindow, 13, 34, "[2] Langue");
        mvwprintw(welcomeWindow, 15, 34, "[3] A propos de nous");
        break;
      default:
        mvwprintw(welcomeWindow, 11, 34, "[1] Se connecter");
        mvwprintw(welcomeWindow, 13, 34, "[2] S'inscrire");
        mvwprintw(welcomeWindow, 15, 34, "[3] Langue");
        mvwprintw(welcomeWindow, 17, 34, "[4] A propos de nous");
        break;
    }

    print_in_hmiddle_of_window(
      welcomeWindow,
      26,
      MAX_WIN_COLS,
      currentQuote
    );

    mvwprintw(welcomeWindow, 1, 1, "*%c*", ctrl);
    if (ctrl == '\t') {
      currentTab = next_tab(currentTab, TABS_NUMBER);
      currentQuote = get_random_motivational_quote(get_user_role_from_tab(currentTab));
      // wclear(welcomeWindow);
      ctrl = 0;
    } else if (ctrl == '2' && currentTab != 2) {
      break;
    }

    wrefresh(welcomeWindow);
    ctrl = getch();
  }

  wclear(welcomeWindow);
  free(tabs);
  delwin(welcomeWindow);

  if (ctrl != KEY_F(1)) {
     switch (get_user_role_from_tab(currentTab)) {
      case ADMIN:
        nextRoute = ADMIN_LOGIN;
        break;
      case INSTRUCTOR:
        switch (ctrl) {
          case '1':
            nextRoute = INSTRUCTOR_LOGIN;
            break;
          case '2':
            nextRoute = INSTRUCTOR_REGISTER;
            break;
        }
        break;
      default :
        switch (ctrl) {
          case '1':
            nextRoute = LEARNER_LOGIN;
            break;
          case '2':
            nextRoute = LEARNER_REGISTER;
            break;
        }
       break;
    }
  }

  return nextRoute;
}

int next_tab(int current_tab, int total_tabs) {
  return (current_tab + 1) % total_tabs;
}

UserRole get_user_role_from_tab(int tab_index) {
  switch (tab_index) {
    case 0:
      return LEARNER;
    case 1:
      return INSTRUCTOR;
    case 2:
      return ADMIN;
    default:
      return LEARNER; // Default to LEARNER if invalid index
  }
}