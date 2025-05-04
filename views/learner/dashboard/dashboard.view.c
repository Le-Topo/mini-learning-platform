//
// Created by astrid on 2025-04-26.
//

#include "./dashboard.view.h"

Route render_learner_dashboard_view()
{
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    clear();

    int ctrl = -1;
    const LearnerSidebarItem currentSidebarPage = LEARNER_DASHBOARD;

    char *pageTitle = get_learner_sidebar_item_name(currentSidebarPage);

    wattron(stdscr, COLOR_PAIR(5));
    mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a la page precedente et la touche F12 pour quitter");
    wattroff(stdscr, COLOR_PAIR(5));


    render_learner_sidebar(stdscr, currentSidebarPage);
    //    refresh();

    Route nextRoute = ROUTE_EXIT;
    //    bool shouldRefreshScreen = true;


    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
        if (can_handle_pressed_key_in_learner_sidebar(ctrl)) {
            nextRoute = get_learner_page_route_from_key(ctrl);
            break;
        }

        ctrl = getch();
    }

    set_route_from_exit_keys(ctrl, &nextRoute);
    return nextRoute;
}