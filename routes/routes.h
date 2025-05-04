//
// Created by astrid on 2025-04-13.
//

#ifndef ROUTES_H
#define ROUTES_H

#include <stdlib.h>
#include "../utils/logs/logger.h"

enum Route {
  ROUTE_EXIT,
  ROUTE_BACK,

  ROUTE_WELCOME,

  ROUTE_INSTRUCTOR_REGISTER,
  ROUTE_INSTRUCTOR_LOGIN,
  ROUTE_INSTRUCTOR_DASHBOARD,
  ROUTE_INSTRUCTOR_NEW_COURSE,
  ROUTE_INSTRUCTOR_COURSES,
  ROUTE_INSTRUCTOR_NOTIFICATIONS,
  ROUTE_INSTRUCTOR_SETTINGS,

  ROUTE_LEARNER_REGISTER,
  ROUTE_LEARNER_LOGIN,
  ROUTE_LEARNER_DASHBOARD,
  ROUTE_LEARNER_COURSES,
  ROUTE_LEARNER_TAKEN_COURSES,
  ROUTE_LEARNER_NOTIFICATIONS,
  ROUTE_LEARNER_SETTINGS,
  ROUTE_LEARNER_COURSE_DETAILS,

  ROUTE_ADMIN_LOGIN,

  ROUTE_LOGOUT
};
typedef enum Route Route;

Route* add_route_to_execution_stack(Route *stack, const Route route, int *currentStackSize, int *currentRouteIndex);

#endif //ROUTES_H
