//
// Created by astri on 2025-04-17.
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
    void *fieldPtr = (char*)struct_ptr + fields[i].offset;

    binds[i].buffer_type = fields[i].type;
    binds[i].buffer = fieldPtr;

    if (fields[i].type == MYSQL_TYPE_STRING) {
      binds[i].buffer_length = fields[i].length;
      binds[i].is_null = 0;
      binds[i].length = &binds[i].buffer_length;
      binds[i].buffer = *(char**)fieldPtr;
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
//    for (int i = 0; i < resultFieldsCount; i++) {
//      log_message("%s ", row[i]);
//    }
    callback(row, resultFields, resultFieldsCount, context);
  }

//  MYSQL_STMT *stmt = mysql_stmt_init(conn);
//  if (!stmt) {
//    log_message("mysql_stmt_init() failed");
//    return QUERY_SERVER_ERROR;
//  }
//
//  if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
//    log_message("mysql_stmt_prepare() failed: %s", mysql_stmt_error(stmt));
//    mysql_stmt_close(stmt);
//    return QUERY_SERVER_ERROR;
//  }
//
//  MYSQL_BIND *binds = calloc(count, sizeof(MYSQL_BIND));
//  if (!binds) {
//    log_message("Memory allocation failed");
//    mysql_stmt_close(stmt);
//    return QUERY_SERVER_ERROR;
//  }
//
//  bind_results_from_struct(binds, fields, count, data);
//
//  for (int i = 0; i < count; ++i) {
//    log_message("bind[%d] -> type: %d | buffer: %p | len: %lu",
//                i, binds[i].buffer_type, binds[i].buffer, binds[i].buffer_length);
//  }
//
//  if (mysql_stmt_bind_result(stmt, binds) != 0) {
//    log_message("mysql_stmt_bind_result() failed: %s", mysql_stmt_error(stmt));
//    free(binds);
//    mysql_stmt_close(stmt);
//    return QUERY_SERVER_ERROR;
//  }
//
//  if (mysql_stmt_execute(stmt) != 0) {
//    log_message("mysql_stmt_execute() failed: %s", mysql_stmt_error(stmt));
//    free(binds);
//    mysql_stmt_close(stmt);
//    return QUERY_SERVER_ERROR;
//  }
//
//  while (mysql_stmt_fetch(stmt) == 0) {
////    callback(data, context);
//  }
//
//  free(binds);
//  mysql_stmt_close(stmt);
  return QUERY_SUCCESS;
}