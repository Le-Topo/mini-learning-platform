//
// Created by astrid on 2025-04-26.
//

#ifndef COURSES_VIEW_H
#define COURSES_VIEW_H

#include <curses.h>
#include "../learner.layout.h"
#include "../../../routes/routes.h"
#include "../../../utils/functions/functions.h"
#include "../../../models/course.h"
#include "../course-details/course-details.view.h"

Route render_learner_courses_view();

void refresh_courses_list(WINDOW *win, CourseList *pCoursesList);

#endif //COURSES_VIEW_H
