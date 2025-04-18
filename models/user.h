//
// Created by astrid on 2025-04-07.
//

#ifndef USER_H
#define USER_H

#include "../utils/enums/user-role.h"
#include "../utils/database/db-connection.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../utils/logs/logger.h"
#include "../utils/database/db-orm.h"
#include "../utils/enums/query-response-status.h"

#define USERS_TABLE "users"

struct User {
  long id;
  char *email;
  char *password;
  char *firstname;
  char *lastname;
  char *distinction; // Disctions of the user, if applicable (e.g: Ing., Dr., etc.)
  UserRole role;

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct User User;

QueryResponseStatus create_user(char *email, char *password, char *firstname, char *lastname, UserRole role);

#endif //USER_H
