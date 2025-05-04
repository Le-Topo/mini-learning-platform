#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "../../models/user.h"
#include "../../utils//functions/functions.h"
#include "../../utils/session-handler/session-handler.h"

void register_user(char *email, char *password, char *firstname, char *lastname, UserRole role);

void login_user(char *email, char *password, UserRole role, User *user);

void logout_user();

#endif //AUTH_CONTROLLER_H
