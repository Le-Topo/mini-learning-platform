#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "utils/database/db-connection.h"

int main(int argc, char *argv[]) {
  printf("Hello, World!\n");
    // Get the MySQL connection
    MYSQL *conn = get_mysql_connection();

    mysql_close(conn);

    return EXIT_SUCCESS;
}
