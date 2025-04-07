//
// Created by astrid on 2025-04-07.
//

#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <mysql/mysql.h>
#include "./db-credentials.h"
#include "../logs/logger.h"

// This function initializes a MySQL connection and returns it.
MYSQL *get_mysql_connection();


#endif //DB_CONNECTION_H
