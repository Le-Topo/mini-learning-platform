//
// Created by astrid on 2025-04-07.
//

#ifndef USER_H
#define USER_H

#include "utils/enums/user-role.h"

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

#endif //USER_H
