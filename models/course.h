//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_H
#define COURSE_H

#include <stdbool.h>
#include "../utils/enums/course-level.h"
#include "../utils/database/db-orm.h"

#define COURSES_TABLE "courses"

typedef struct Course Course;
struct Course {
  long id;
  long instructor_id; // ID of the instructor who created the course
  char title[100];
  char description[200];
  CourseLevel level;
  int duration; // in hours
  char tags[100]; // comma-separated tags
  bool is_validated; // true if the course is validated by an administrator
  char validation_message[50]; // message from the administrator

  char created_at[50]; // ISO 8601 format
  char updated_at[50]; // ISO 8601 format

  Course *next; // Pointer to the next course in the list
  Course *prev; // Pointer to the previous course in the list
};

struct CourseList {
  Course *head;
  int count;
};
typedef struct CourseList CourseList;

QueryResponseStatus get_courses(char *title, bool validated, CourseList **course_list_ptr);

Course* convert_mysql_fetched_row_to_course(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields);

void add_fetched_course_to_list(MYSQL_ROW courseRow, MYSQL_FIELD *fields, int num_fields, void **course_list_ptr);

#endif //COURSE_H
