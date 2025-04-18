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
//  size_t length;
} FieldMapping;


// Bindings functions
void bind_results_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr);
void bind_params_from_struct(MYSQL_BIND *binds, const FieldMapping *fields, int fields_count, void *struct_ptr);

// Generic ORM functions
QueryResponseStatus insert_into_table(MYSQL *conn, const char *table, const FieldMapping *fields, int count, void *data);
QueryResponseStatus select_from_table(MYSQL *conn, const char *table, const char *select, const char *clause, const FieldMapping *fields, int count, void *data, void (*callback)(void*));


#endif //DB_ORM_H
