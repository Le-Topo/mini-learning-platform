//
// Created by astrid on 2025-04-25.
//

#ifndef NEW_COURSE_VIEW_H
#define NEW_COURSE_VIEW_H

#include <form.h>
#include "../instructor.layout.h"
#include "../../../routes/routes.h"
#include "../../../models/course.h"
#include "../../../models/course-part.h"

#define STEPS_COUNT 3

typedef enum NewCourseFormStep {
    NEW_COURSE_FORM_COURSE_PROPERTIES_STEP = 0,
    NEW_COURSE_FORM_COURSE_OVERVIEW_STEP = 1,
    NEW_COURSE_FORM_NEW_TEXT_CONTENT_STEP = 2,
} NewCourseFormStep;

Route render_instructor_new_course_view();

void render_new_course_appropriate_form(WINDOW *win, NewCourseFormStep step);

FieldProps *get_new_course_form_fields_props(NewCourseFormStep step, int *fieldsCount);

void sync_course_properties_with_form(FIELD **fields, Course *course);

void sync_course_parts_properties_with_form(FIELD **fields, CoursePart *course_parts, int course_parts_count);

void setup_course_properties_form_validation(FIELD **fields);

void clear_screen();

#endif //NEW_COURSE_VIEW_H
