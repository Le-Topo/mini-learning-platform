//
// Created by astrid on 2025-04-07.
//

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "./db-connection.h"
#include "./db-credentials.h"
#include "../logs/logger.h"

// This function uses a static variable to ensure that the connection is only created once.
MYSQL *get_mysql_connection() {
  static MYSQL *conn = NULL;

  if (conn == NULL) {
    log_message("MySQL initialization...");
    conn = mysql_init(NULL);
    if (conn == NULL) {
      log_message("Failed to initialize MySQL !");
      exit(EXIT_FAILURE);
    } else {
      log_message("MySQL has been initialized successfully !");
    }

    log_message("Connecting to MySQL...");
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
      log_message("Failed to connect to MySQL : %s\n", mysql_error(conn));
      mysql_close(conn);
      conn = NULL;
      exit(EXIT_FAILURE);
    } else {
      log_message("Connection to MySQL has been established successfully !");
    }
  }

  return conn;
}