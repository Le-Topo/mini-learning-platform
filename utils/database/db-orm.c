//
// Created by astri on 2025-04-17.
//

#include "./db-orm.h"

// Function to bind results from a struct to MYSQL_BIND array
void bind_results_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr)
{
  for (int i = 0; i < fields_count; ++i) {
    void *addr = (char*)struct_ptr + fields[i].offset;
    binds[i].buffer_type = fields[i].type;
    binds[i].buffer = addr;

    if (fields[i].type == MYSQL_TYPE_STRING || fields[i].type == MYSQL_TYPE_VAR_STRING) {
      log_message("BBinding %s to %s", fields[i].column_name, (char*)addr);
      binds[i].buffer_length = strlen(binds[i].buffer);
    }
  }
}

// Function to bind parameters from a struct to MYSQL_BIND array
void bind_params_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr)
{
  for (int i = 0; i < fields_count; ++i) {
    void *field_ptr = (char*)struct_ptr + fields[i].offset;

    binds[i].buffer_type = fields[i].type;
    binds[i].buffer = field_ptr;

    if (fields[i].type == MYSQL_TYPE_STRING) {
      binds[i].buffer_length = strlen(*(char**)field_ptr);
      binds[i].is_null = 0;
      binds[i].length = &binds[i].buffer_length;
      binds[i].buffer = *(char**)field_ptr;
    }
    else {
      binds[i].is_null = 0;
      binds[i].length = 0;
    }
  }
}

// Function to insert data into a table
QueryResponseStatus insert_into_table(MYSQL *conn, const char *table, const FieldMapping *fields, int count, void *data)
{
  MYSQL_STMT *stmt = mysql_stmt_init(conn);
  MYSQL_BIND *binds = calloc(count, sizeof(MYSQL_BIND));
  char query[256] = {0};
  char values[128] = {0};

  strcat(query, "INSERT INTO ");
  strcat(query, table);
  strcat(query, " (");
  for (int i = 0; i < count; ++i) {
    strcat(query, fields[i].column_name);
    if (i < count - 1) {
      strcat(query, ", ");
    }
  }
  strcat(query, ") VALUES (");

  for (int i = 0; i < count; ++i) {
    strcat(query, (i == 0) ? "?" : ",?");
  }
  strcat(query, ")");

  log_message("Query: %s", query);
  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
    log_message("mysql_stmt_prepare() failed: %s", mysql_stmt_error(stmt));
    mysql_stmt_close(stmt);
    free(binds);
    return QUERY_SERVER_ERROR;
  }

  bind_params_from_struct(binds, fields, count, data);

  if (mysql_stmt_bind_param(stmt, binds) != 0) {
    log_message("mysql_stmt_bind_param() failed: %s", mysql_stmt_error(stmt));
    mysql_stmt_close(stmt);
    free(binds);
    return QUERY_SERVER_ERROR;
  }

  log_message("%s %s %s", binds[0].buffer, binds[1].buffer, binds[2].buffer);

  int status = mysql_stmt_execute(stmt);

  mysql_stmt_close(stmt);
  free(binds);

  if (status != 0) {
    log_message("Unable to execute query statement : %s", mysql_stmt_error(stmt));
    return QUERY_SERVER_ERROR;
  }
  return QUERY_SUCCESS;
}

// Function to select data from a table and call a callback function for each row
QueryResponseStatus select_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, const FieldMapping *fields, int count, void *data, void (*callback)(void*))
{
  char query[256];

  snprintf(query, sizeof(query), "SELECT %s FROM %s %s", select, table, clause);

  MYSQL_STMT *stmt = mysql_stmt_init(conn);
  if (!stmt) {
    log_message("mysql_stmt_init() failed");
    return QUERY_SERVER_ERROR;
  }

  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
    mysql_stmt_close(stmt);
    log_message("mysql_stmt_prepare() failed: %s", mysql_stmt_error(stmt));
    return QUERY_SERVER_ERROR;
  }

  MYSQL_BIND *binds = calloc(count, sizeof(MYSQL_BIND));
  if (!binds) {
    mysql_stmt_close(stmt);
    log_message("Memory allocation failed");
    return QUERY_SERVER_ERROR;
  }

  bind_results_from_struct(binds, fields, count, data);

  if (mysql_stmt_bind_result(stmt, binds) != 0) {
    free(binds);
    mysql_stmt_close(stmt);
    log_message("mysql_stmt_bind_result() failed: %s", mysql_stmt_error(stmt));
    return QUERY_SERVER_ERROR;
  }

  if (mysql_stmt_execute(stmt) != 0) {
    free(binds);
    mysql_stmt_close(stmt);
    log_message("mysql_stmt_execute() failed: %s", mysql_stmt_error(stmt));
    return QUERY_SERVER_ERROR;
  }

  while (mysql_stmt_fetch(stmt) == 0) {
    callback(data);
  }

  free(binds);
  mysql_stmt_close(stmt);
  return QUERY_SUCCESS;
}