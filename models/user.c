//
// Created by astri on 2025-04-17.
//

#include "./user.h"

QueryResponseStatus create_user(char *email, char *password, char *firstname, char *lastname, UserRole role)
{
  MYSQL *conn = get_mysql_connection();

  FieldMapping user_insert_schema[] = {
    { "firstname", MYSQL_TYPE_STRING, offsetof(User, firstname), sizeof(((User *)0)->firstname) },
    { "lastname", MYSQL_TYPE_STRING, offsetof(User, lastname), sizeof(((User *)0)->lastname) },
    { "email", MYSQL_TYPE_STRING, offsetof(User, email), sizeof(((User *)0)->email) },
    { "password", MYSQL_TYPE_STRING, offsetof(User, password), sizeof(((User *)0)->password) },
    { "role", MYSQL_TYPE_TINY, offsetof(User, role), 0 }
  };

  User user = {
    .firstname = firstname,
    .lastname = lastname,
    .email = email,
    .password = password,
    .role = role
  };

//  log_message("Inserting user: %s %s %s %s", user.firstname, user.lastname, user.email, user.password);

  return insert_into_table(conn, USERS_TABLE, user_insert_schema, sizeof(user_insert_schema) / sizeof(FieldMapping), &user);

//  const char *query = "INSERT INTO users (email, password, firstname, lastname, role) VALUES (?, ?, ?, ?, ?)";
//  MYSQL_STMT *stmt = mysql_stmt_init(conn);
//
//  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
//      log_message("mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
//      mysql_stmt_close(stmt);
//      return false;
//  }
//
//
//  MYSQL_BIND bind[5];
//  memset(bind, 0, sizeof(bind));
//
//  bind[0].buffer_type = MYSQL_TYPE_STRING;
//  bind[0].buffer = (char *)email;
//  bind[0].buffer_length = strlen(email);
//
//  bind[1].buffer_type = MYSQL_TYPE_STRING;
//  bind[1].buffer = (char *)password;
//  bind[1].buffer_length = strlen(password);
//
//  bind[2].buffer_type = MYSQL_TYPE_STRING;
//    bind[2].buffer = (char *)firstname;
//    bind[2].buffer_length = strlen(firstname);
//
//    bind[3].buffer_type = MYSQL_TYPE_STRING;
//    bind[3].buffer = (char *)lastname;
//    bind[3].buffer_length = strlen(lastname);
//
//    bind[4].buffer_type = MYSQL_TYPE_TINY;
//    bind[4].buffer = (char *)&role;
//    bind[1].is_null = 0;
//    bind[1].length = 0;
//
//    if (mysql_stmt_bind_param(stmt, bind) != 0) {
//        log_message("Binding error for statement : %s\n", mysql_stmt_error(stmt));
//        return false;
//    }
//
//    if (mysql_stmt_execute(stmt) != 0) {
//        log_message("Unable to execute query statement : %s\n", mysql_stmt_error(stmt));
//        return false;
//    }
//
//    mysql_stmt_close(stmt);
//    return true;
}