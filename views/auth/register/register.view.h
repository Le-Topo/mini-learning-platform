//
// Created by astri on 2025-04-09.
//

#ifndef REGISTER_VIEW_H
#define REGISTER_VIEW_H

// #include "../../../lib/pdcurses/include/curses.h"
#include "../../../utils/enums/user-role.h"
#include "../../../utils/curses/curses-utilities.h"
#include "../../../utils/functions/functions.h"
#include "../../../routes/routes.h"
#include <curses.h>

Route render_register_view(UserRole user_role);

#endif //REGISTER_VIEW_H
