//
// Created by astrid on 2025-04-07.
//

#ifndef SESSION_H
#define SESSION_H

#include "../utils/database/db-orm.h"
#define SESSIONS_TABLE "sessions"

struct Session {
  long id;
  long user_id; // Foreign key to User
  char *closed_at; // Timestamp of when the session was closed

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct Session Session;

QueryResponseStatus create_session(long user_id);

QueryResponseStatus close_session(long user_id);

#endif //SESSION_H
