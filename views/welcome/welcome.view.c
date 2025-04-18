//
// Created by astri on 2025-04-11.
//
#include "welcome.view.h"

#define TABS_NUMBER 3

Route render_welcome_view()
{
  // WINDOW *welcomeWindow = newwin(MAX_WIN_LINES, MAX_WIN_COLS, 0, 0);
  int ctrl = -1;
  const char *pageTitle = "Bienvenue sur Mini Leanrning Platform !";
  char **tabs = malloc(sizeof(char *) * TABS_NUMBER);
  tabs[0] = "Apprenant";
  tabs[1] = "Instructeur";
  tabs[2] = "Administrateur";
  bool hasFocus = false;

  int currentTab = 0;
  char *currentQuote = get_random_motivational_quote(get_user_role_from_tab(currentTab));
  bool shouldRefreshScreen = true;

  Route nextRoute = EXIT;

  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  clear();

  wattron(stdscr, COLOR_PAIR(5));
  mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche TAB pour naviguer entre les onglets et la touche F12 pour quitter");
  wattroff(stdscr, COLOR_PAIR(5));

  print_in_hmiddle_of_window(stdscr, 2, MAX_WIN_COLS, pageTitle);

  int i = 1;
  while (ctrl != EXIT_KEY) {
    if (shouldRefreshScreen) {
      mvprintw(11, 34, BLANK_LINE);
      mvprintw(13, 34, BLANK_LINE);
      mvprintw(15, 34, BLANK_LINE);
      mvprintw(17, 34, BLANK_LINE);
      print_in_hmiddle_of_window(stdscr, 26, MAX_WIN_COLS, LONG_BLANK_LINE);


      currentQuote = get_random_motivational_quote(get_user_role_from_tab(currentTab));
      print_in_hmiddle_of_window(
        stdscr,
        26,
        MAX_WIN_COLS,
        currentQuote
      );

      int tabX = 34;
      int tabY = 5;
      for (int i = 0; i < TABS_NUMBER; i++) {
        if (i == currentTab) {
          wattron(stdscr, COLOR_PAIR(4));
        }

        draw_rectangle_with_text(stdscr, &tabX, &tabY, tabs[i], 6, 1, false, MAX_WIN_COLS);
        tabY -= 2;

        if (i == currentTab) {
          wattroff(stdscr, COLOR_PAIR(4));
        }
      }

      draw_rectangle(stdscr, 30, 8, tabX-26, 16);

      switch(get_user_role_from_tab(currentTab)) {
        case ADMIN:
          mvprintw(11, 34, "[1] Se connecter");
          mvprintw(13, 34, "[2] Langue");
          mvprintw(15, 34, "[3] A propos de nous");
        break;
        default:
          mvprintw(11, 34, "[1] Se connecter");
          mvprintw(13, 34, "[2] S'inscrire");
          mvprintw(15, 34, "[3] Langue");
          mvprintw(17, 34, "[4] A propos de nous");
        break;
      }

      refresh();
      shouldRefreshScreen = false;
    }

    ctrl = getch();

    if (ctrl == '\t') {
      currentTab = next_tab(currentTab, TABS_NUMBER);
      shouldRefreshScreen = true;
      ctrl = -1;
    } else if (ctrl == '1' || (ctrl == '2' && currentTab != 2)) {
      break;
    }
  }

  // wclear(welcomeWindow);
  free(tabs);
  // delwin(welcomeWindow);

  if (ctrl != EXIT_KEY) {
    switch (ctrl) {
      case '1':
        if (currentTab == 0) {
          nextRoute = LEARNER_LOGIN;
        } else if (currentTab == 1) {
          nextRoute = INSTRUCTOR_LOGIN;
        } else {
          nextRoute = ADMIN_LOGIN;
        }
        break;
      case '2':
        if (currentTab == 0) {
          nextRoute = LEARNER_REGISTER;
        } else if (currentTab == 1) {
          nextRoute = INSTRUCTOR_REGISTER;
        }
        break;
      default:
        nextRoute = EXIT;
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