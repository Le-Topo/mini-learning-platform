//
// Created by astri on 2025-04-07.
//

#ifndef SESSION_H
#define SESSION_H

struct Session {
  long id;
  long user_id; // Foreign key to User
  char *closed_at; // Timestamp of when the session was closed

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct Session Session;

#endif //SESSION_H
