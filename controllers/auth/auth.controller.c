//
// Created by astri on 2025-04-09.
//

#include "./auth.controller.h"

void register_user(char *email, char *password, char *firstname, char *lastname, UserRole role)
{
    create_user(email, hash_string(password), firstname, lastname, role);
    User user = {0};
    login_user(email, password, role, &user);
}

void login_user(char *email, char *password, UserRole role, User *user)
{
    QueryResponseStatus status = get_user_by_email_and_password(email, hash_string(password), role, user);
    if (status != QUERY_SUCCESS) {
        log_message("Login failed: %s", mysql_error(get_mysql_connection()));
    } else {
        if (user->id != 0) {
            initialize_session(*user);
        }
    }
}

void logout_user()
{
    destroy_session();
}