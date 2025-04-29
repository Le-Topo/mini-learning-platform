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
  char email[40];
  char password[40];
  char firstname[40];
  char lastname[40];
  char distinction[50]; // Disctions of the user, if applicable (e.g: Ing., Dr., etc.)
  UserRole role;

  char created_at[50]; // ISO 8601 format
  char updated_at[50]; // ISO 8601 format
};
typedef struct User User;

QueryResponseStatus create_user(char *email, char *password, char *firstname, char *lastname, UserRole role);

QueryResponseStatus email_exists(char *email, bool *exists);

QueryResponseStatus get_user_by_email_and_password(char *email, char *password, UserRole role, User *user);

QueryResponseStatus get_user_by_id(long id, User *user);

void convert_mysql_fetched_row_to_user(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields, void *user);

#endif //USER_H
