//
// Created by astri on 2025-04-17.
//

#include "./dashboard.view.h"

Route render_instructor_dashboard_view()
{
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    clear();

    int ctrl = -1;
    const InstructorSidebarItem currentSidebarPage = INSTRUCTOR_DASHBOARD;

    char *pageTitle = get_instructor_sidebar_item_name(currentSidebarPage);

    wattron(stdscr, COLOR_PAIR(5));
    mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a la page precedente et la touche F12 pour quitter");
    wattroff(stdscr, COLOR_PAIR(5));


    render_instructor_sidebar(stdscr, currentSidebarPage);
//    refresh();

    Route nextRoute = EXIT;
//    bool shouldRefreshScreen = true;


    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
        ctrl = getch();
    }

    return nextRoute;
}