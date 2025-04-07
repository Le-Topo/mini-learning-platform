//
// Created by astrid on 2025-04-07.
//

#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H

#include <stdbool.h>

struct QuizQuestion {
  long id;
  long course_part_id; // Foreign key to the quiz course part
  char *label; // Question label
  bool has_multiple_answers; // true if the question has multiple answers, false if it's a single answer
  int order; // Order of the question in the quiz

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct QuizQuestion QuizQuestion;

#endif //QUIZ_QUESTION_H
