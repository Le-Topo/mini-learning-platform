//
// Created by astrid on 2025-04-27.
//

#ifndef SESSION_HANDLER_H
#define SESSION_HANDLER_H

#include <stdlib.h>
#include "../../models/session.h"
#include "../../models/user.h"

void initialize_session(User user);

void destroy_session();

void set_session_user(User user);

User get_session_user();

#endif //SESSION_HANDLER_H
