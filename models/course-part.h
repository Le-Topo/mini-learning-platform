//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_PART_H
#define COURSE_PART_H

#include <stdbool.h>
#include "../utils/database/db-orm.h"
#include "../utils/enums/query-response-status.h"

#define COURSE_PARTS_TABLE "course_parts"

struct CoursePart {
  long id;
  long course_id; // Foreign key to Course
  char title[70];
  bool is_quiz; // true if the part is a quiz, false if it's a text
  char content[1000]; // Content of the part if it's a text
  int order; // Order of the part in the course
  int score_percentage; // Percentage of the total score for this part if it's a quiz

  char created_at[50]; // ISO 8601 format
  char updated_at[50]; // ISO 8601 format

  struct CoursePart *next; // Pointer to the next part in the list
  struct CoursePart *prev; // Pointer to the previous part in the list
};
typedef struct CoursePart CoursePart;

struct CoursePartList {
  CoursePart *head;
  int count;
};
typedef struct CoursePartList CoursePartList;


QueryResponseStatus get_course_parts_by_course_id(long course_id, CoursePartList **course_parts_list_ptr);

CoursePart* convert_mysql_fetched_row_to_course_part(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields);

void add_fetched_course_part_to_list(MYSQL_ROW courseRow, MYSQL_FIELD *fields, int num_fields, void **course_parts_list_ptr);

#endif //COURSE_PART_H
