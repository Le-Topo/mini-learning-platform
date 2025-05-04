//
// Created by astrid on 2025-04-17.
//

#include "./db-orm.h"

// Function to bind results from a struct to MYSQL_BIND array
void bind_results_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr)
{
  for (int i = 0; i < fields_count; ++i) {
    memset(&binds[i], 0, sizeof(MYSQL_BIND));
    void *addr = (char *)struct_ptr + fields[i].offset;

    binds[i].buffer_type = fields[i].type;
    binds[i].buffer = addr;

    if (fields[i].type == MYSQL_TYPE_STRING || fields[i].type == MYSQL_TYPE_VAR_STRING) {
        binds[i].buffer_length = fields[i].length;
    }

    log_message("bind[%d] buffer = %p, type = %d, len = %lu\n", i, binds[i].buffer, fields[i].type, fields[i].length);
  }
}

// Function to bind parameters from a struct to MYSQL_BIND array
void bind_params_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr)
{
  for (int i = 0; i < fields_count; ++i) {
    memset(&binds[i], 0, sizeof(MYSQL_BIND));
    void *addr = (char *)struct_ptr + fields[i].offset;

    binds[i].buffer_type = fields[i].type;
    binds[i].buffer = addr;

    if (fields[i].type == MYSQL_TYPE_STRING || fields[i].type == MYSQL_TYPE_VAR_STRING) {
        binds[i].buffer_length = fields[i].length;
        binds[i].length = NULL;
        binds[i].is_null = 0;
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
QueryResponseStatus select_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, void (*callback)(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields, void **context), void **context)
{
  char query[400];

  snprintf(query, sizeof(query), "SELECT %s FROM %s ", select, table);
  strcat(query, clause);
  log_message("Received clause: %s", clause);
  log_message("Executing sql query: %s", query);

  if (mysql_query(conn, query) != 0) {
    log_message("Query error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  if (!result) {
    fprintf(stderr, "Query result error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  int resultFieldsCount = mysql_num_fields(result);
  MYSQL_FIELD *resultFields = mysql_fetch_fields(result);
  MYSQL_ROW row;

  while ((row = mysql_fetch_row(result))) {
    callback(row, resultFields, resultFieldsCount, context);
  }

  mysql_free_result(result);
  return QUERY_SUCCESS;
}

QueryResponseStatus select_one_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, void (*callback)(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields, void *context), void *context)
{
  char query[400];

  snprintf(query, sizeof(query), "SELECT %s FROM %s ", select, table);
  strcat(query, clause);
  strcat(query, " LIMIT 1");
  log_message("Received clause: %s", clause);
  log_message("Executing sql query: %s", query);

  if (mysql_query(conn, query) != 0) {
    log_message("Query error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  if (!result) {
    fprintf(stderr, "Query result error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  int resultFieldsCount = mysql_num_fields(result);
  MYSQL_FIELD *resultFields = mysql_fetch_fields(result);
  MYSQL_ROW row = mysql_fetch_row(result);

  if (row && callback) {
    callback(row, resultFields, resultFieldsCount, context);
  } else {
    log_message("No row found for query: %s", query);
  }

  mysql_free_result(result);
  return QUERY_SUCCESS;
}

QueryResponseStatus select_count_from_table(MYSQL *conn, const char *table, const char *clause, int *count)
{
  char query[400];
  snprintf(query, sizeof(query), "SELECT COUNT(*) FROM %s ", table);
  strcat(query, clause);
  log_message("Executing sql query: %s", query);

  if (mysql_query(conn, query) != 0) {
    log_message("Query error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  MYSQL_RES *result = mysql_store_result(conn);
  if (!result) {
    fprintf(stderr, "Query result error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  MYSQL_ROW row = mysql_fetch_row(result);
  if (row && count) {
    *count = atoi(row[0]);
  }

  mysql_free_result(result);
  return QUERY_SUCCESS;
}


QueryResponseStatus update_table_row(MYSQL *conn, const char *table, const char *new_values_and_clause)
{
  char query[400];

  snprintf(query, sizeof(query), "UPDATE %s SET ", table);
  strcat(query, new_values_and_clause);
  log_message("Received clause: %s", new_values_and_clause);
  log_message("Executing sql query: %s", query);

  if (mysql_query(conn, query) != 0) {
    log_message("Query error : %s\n", mysql_error(conn));
    mysql_close(conn);
    return QUERY_SERVER_ERROR;
  }

  return QUERY_SUCCESS;
}