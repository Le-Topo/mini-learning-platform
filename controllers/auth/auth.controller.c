//
// Created by astri on 2025-04-09.
//

#include "./auth.controller.h"

void register_user(char *email, char *password, char *firstname, char *lastname, UserRole role)
{
    log_message("%d", create_user(email, hash_string(password), firstname, lastname, role));
}