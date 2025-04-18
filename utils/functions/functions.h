//
// Created by astri on 2025-04-11.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include "../enums/user-role.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

char* get_random_motivational_quote(UserRole user_role);

char* get_user_role_description(UserRole user_role);

char* trim_whitespaces(char *str);

char* hash_string(char *str);

#endif //FUNCTIONS_H
