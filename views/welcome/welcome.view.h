//
// Created by astrid on 2025-04-11.
//

#ifndef WELCOME_VIEW_H
#define WELCOME_VIEW_H

#include <stdlib.h>
// #include "../../lib/pdcurses/include/curses.h"
// #include "../../lib/pdcurses/include/panel.h"
#include "../../utils/curses/curses-utilities.h"
#include "../../utils/functions/functions.h"
#include "../../routes/routes.h"
#include <curses.h>


Route render_welcome_view();

int next_tab(int current_tab, int total_tabs);

UserRole get_user_role_from_tab(int tab_index);

#endif //WELCOME_VIEW_H
