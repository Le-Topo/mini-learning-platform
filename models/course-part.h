//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_PART_H
#define COURSE_PART_H

#include <stdbool.h>

struct CoursePart {
  long id;
  long course_id; // Foreign key to Course
  char *title;
  bool is_quiz; // true if the part is a quiz, false if it's a text
  char *content; // Content of the part if it's a text
  int order; // Order of the part in the course
  int score_percentage; // Percentage of the total score for this part if it's a quiz

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct CoursePart CoursePart;

#endif //COURSE_PART_H
