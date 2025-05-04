//
// Created by astrid on 2025-04-17.
//

#ifndef LOGIN_VIEW_H
#define LOGIN_VIEW_H

#include <curses.h>
#include <form.h>
#include <string.h>
#include "../../../utils/enums/user-role.h"
#include "../../../utils/curses/curses-utilities.h"
#include "../../../utils/functions/functions.h"
#include "../../../routes/routes.h"
#include "../../../controllers/auth/auth.controller.h"

Route render_login_view(UserRole user_role);

#endif //LOGIN_VIEW_H
