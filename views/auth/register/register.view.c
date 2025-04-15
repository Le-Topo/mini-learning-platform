//
// Created by astri on 2025-04-09.
//

#include "./register.view.h"

Route render_register_view(UserRole user_role) {
    WINDOW *registerWindow = newwin(MAX_WIN_LINES, MAX_WIN_COLS, 1, 1);
    int ctrl = 0;
    char pageTitle[30];
    sprintf(pageTitle, "Inscription (%s)", get_user_role_description(user_role));
    printf("pageTitle: %s\n", pageTitle);
    Route nextRoute = EXIT;

    clear();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (ctrl != KEY_F(1)) {
        wclear(registerWindow);

        wattron(registerWindow, COLOR_PAIR(5));
        mvwprintw(registerWindow, MAX_WIN_LINES-1, 2, "Utiliser la touche A pour retourner a l'accueil et la touche F1 pour quitter");
        wattroff(registerWindow, COLOR_PAIR(5));

        print_in_hmiddle_of_window(registerWindow, 2, MAX_WIN_COLS, pageTitle);

        wrefresh(registerWindow);
        ctrl = getch();

        if (ctrl == 'a' || ctrl == 'A') {
            nextRoute = WELCOME;
            break;
        }
    }

    return nextRoute;
}