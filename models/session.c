//
// Created by astrid on 2025-04-27.
//

#include "./session.h"

QueryResponseStatus create_session(long user_id) {
    MYSQL *conn = get_mysql_connection();

    FieldMapping session_insert_schema[] = {
        { "user_id", MYSQL_TYPE_LONGLONG, offsetof(Session, user_id), 0 },
    };

    Session session;
    memset(&session, 0, sizeof(Session));
    session.user_id = user_id;

    return insert_into_table(conn, SESSIONS_TABLE, session_insert_schema, sizeof(session_insert_schema) / sizeof(FieldMapping), &session);
}

QueryResponseStatus close_session(long user_id) {
    MYSQL *conn = get_mysql_connection();

    char whereClause[80];
    snprintf(whereClause, sizeof(whereClause), " closed_at = CURRENT_TIMESTAMP WHERE user_id = %ld AND closed_at iS NULL", user_id);
    return update_table_row(conn, SESSIONS_TABLE, whereClause);
}