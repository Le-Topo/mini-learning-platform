//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_H
#define COURSE_H

#include <stdbool.h>
#include "utils/enums/course-level.h"

struct Course {
  long id;
  char *title;
  char *description;
  CourseLevel level;
  int duration; // in hours
  char *tags; // comma-separated tags
  bool is_validated; // true if the course is validated by an administrator
  char *validation_message; // message from the administrator

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct Course Course;

#endif //COURSE_H
  #include <stdio.h>
#include <stdlib.h>

void createcourse(){

  struct u;
  printf("n\ Enter a title : ");
  


}