//
// Created by astrid on 2025-04-17.
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

  User user;
  memset(&user, 0, sizeof(User));
  strncpy(user.firstname, firstname, sizeof(user.firstname));
  strncpy(user.lastname, lastname, sizeof(user.lastname));
  strncpy(user.email, email, sizeof(user.email));
  strncpy(user.password, password, sizeof(user.password));
  user.role = role;

  log_message("Inserting user: %s %s %s %s", user.firstname, user.lastname, user.email, user.password);

  return insert_into_table(conn, USERS_TABLE, user_insert_schema, sizeof(user_insert_schema) / sizeof(FieldMapping), &user);
}

QueryResponseStatus email_exists(char *email, bool *exists)
{
  MYSQL *conn = get_mysql_connection();

  char whereClause[80];
  snprintf(whereClause, sizeof(whereClause), "WHERE email = '%s'", email);

  int count = 0;
  QueryResponseStatus status = select_count_from_table(
    conn,
    USERS_TABLE,
    whereClause,
    &count
  );

  if (status != QUERY_SUCCESS) {
    log_message("Unable to check if email exists: %s", mysql_error(conn));
    return status;
  }
  *exists = (count > 0);

  return QUERY_SUCCESS;
}

QueryResponseStatus get_user_by_email_and_password(char *email, char *password, UserRole role, User *user)
{
  MYSQL *conn = get_mysql_connection();

  char whereClause[80];
  snprintf(whereClause, sizeof(whereClause), " WHERE email = '%s' AND password = '%s' AND role = %d ", email, password, role);

  return select_one_from_table(
    conn,
    USERS_TABLE,
    "*",
    whereClause,
    convert_mysql_fetched_row_to_user,
    (void*) user
  );
}

void convert_mysql_fetched_row_to_user(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields, void *user)
{
  log_message("Converting MySQL fetched row to User");
  if (!user) return;
  User *user_ptr = (User *)user;

  for (int i = 0; i < num_fields; i++) {
    const char *name = fields[i].name;
    const char *value = row[i];

    if (strcmp(name, "firstname") == 0) {
      strncpy(user_ptr->firstname, value, sizeof(user_ptr->firstname));
    } else if (strcmp(name, "lastname") == 0) {
      strncpy(user_ptr->lastname, value, sizeof(user_ptr->lastname));
    } else if (strcmp(name, "email") == 0) {
      strncpy(user_ptr->email, value, sizeof(user_ptr->email));
    } else if (strcmp(name, "password") == 0) {
      strncpy(user_ptr->password, value, sizeof(user_ptr->password));
    } else if (strcmp(name, "role") == 0) {
      user_ptr->role = atoi(value);
    } else if (strcmp(name, "id") == 0) {
      user_ptr->id = atol(value);
    } else if (strcmp(name, "distinction") == 0 && value != NULL) {
      strncpy(user_ptr->distinction, value, sizeof(user_ptr->distinction));
    } else if (strcmp(name, "created_at") == 0 && value != NULL) {
      strncpy(user_ptr->created_at, value, sizeof(user_ptr->created_at));
    } else if (strcmp(name, "updated_at") == 0 && value != NULL) {
      strncpy(user_ptr->updated_at, value, sizeof(user_ptr->updated_at));
    }
  }

}

QueryResponseStatus get_user_by_id(long id, User *user)
{
  MYSQL *conn = get_mysql_connection();

  char whereClause[80];
  snprintf(whereClause, sizeof(whereClause), " WHERE id = %ld", id);

  return select_one_from_table(
    conn,
    USERS_TABLE,
    "*",
    whereClause,
    convert_mysql_fetched_row_to_user,
    (void*) user
  );
}