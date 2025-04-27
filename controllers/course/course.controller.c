//
// Created by astri on 2025-04-26.
//
#include "./course.controller.h"

QueryResponseStatus get_validated_courses(char *title, CourseList **courses_list_ptr) {
  return get_courses(title, true, courses_list_ptr);
}