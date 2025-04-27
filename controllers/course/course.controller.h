//
// Created by astri on 2025-04-26.
//

#ifndef COURSE_CONTROLLER_H
#define COURSE_CONTROLLER_H

#include "../../utils/enums/query-response-status.h"
#include "../../models/course.h"

QueryResponseStatus get_validated_courses(char *title, CourseList **courses_list_ptr);

#endif //COURSE_CONTROLLER_H
