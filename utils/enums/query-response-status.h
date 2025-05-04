//
// Created by astrid on 2025-04-17.
//

#ifndef QUERY_RESPONSE_STATUS_H
#define QUERY_RESPONSE_STATUS_H

enum QueryResponseStatus {
  QUERY_SUCCESS = 0,
  QUERY_SERVER_ERROR = 1,
  QUERY_CLIENT_ERROR = 2,
};
typedef enum QueryResponseStatus QueryResponseStatus;

#endif //QUERY_RESPONSE_STATUS_H
