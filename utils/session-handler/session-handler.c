//
// Created by astri on 2025-04-27.
//

#include "./session-handler.h"

static User loggedInUser;

void initialize_session(User user) {
    loggedInUser = user;
    create_session(user.id);
    log_message("Session initialized for user: %s", user.email);
}

void destroy_session() {
    close_session(loggedInUser.id);
    loggedInUser = (User){0}; // Reset the user
    log_message("Session destroyed for user: %s", loggedInUser.email);
}

void set_session_user(User user) {
    loggedInUser = user;
}

User get_session_user() {
    return loggedInUser;
}
