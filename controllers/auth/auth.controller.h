//
// Created by astri on 2025-04-09.
//

#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include "../../models/user.h"
#include "../../utils//functions/functions.h"

void register_user(char *email, char *password, char *firstname, char *lastname, UserRole role);

#endif //AUTH_CONTROLLER_H
