//
// Created by astri on 2025-04-28.
//

#ifndef INSTRUCTOR_CONTROLLER_H
#define INSTRUCTOR_CONTROLLER_H

#include "../../models/user.h"
#include "../../utils/enums/query-response-status.h"


QueryResponseStatus get_instructor_by_id(long id, User *instructor);

#endif //INSTRUCTOR_CONTROLLER_H
