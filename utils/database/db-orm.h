//
// Created by astri on 2025-04-17.
//

#ifndef DB_ORM_H
#define DB_ORM_H

#include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include "../database/db-connection.h"
#include "../enums/query-response-status.h"

typedef struct {
  const char *column_name;
  enum enum_field_types type;
  size_t offset;
  unsigned long length;
} FieldMapping;


// Bindings functions
void bind_results_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr);
void bind_params_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr);

// Generic ORM functions
QueryResponseStatus insert_into_table(MYSQL *conn, const char *table, const FieldMapping *fields, int count, void *data);

/*
  This function is a bit tricky, because after querying, we'll have to handle the result for each row
  The table parameter is the name of the table to select from
  The select parameter is the columns to select, separated by commas or "*"
  The clause parameter is the WHERE clause, if needed
  The fields parameter is an array of FieldMapping structs that map the columns to the struct fields
  The count parameter is the number of fields in the fields array
  The data parameter is a pointer to the struct that will hold the result for each row
  The callback parameter is a function pointer that will be called for each row, with the row data and the context
*/
// QueryResponseStatus select_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, const FieldMapping *fields, int count, void *data, void (*callback)(void *row, void *context), void *context);

QueryResponseStatus select_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, void (*callback)(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields, void **context), void **context);

#endif //DB_ORM_H
