//
// Created by astrid on 2025-04-07.
//

#ifndef QUIZ_QUESTION_H
#define QUIZ_QUESTION_H

#include <stdbool.h>
#include "../utils/database/db-orm.h"
#include "../utils/enums/query-response-status.h"

#define QUIZ_QUESTIONS_TABLE "quiz_questions"

struct QuizQuestion {
  long id;
  long course_part_id; // Foreign key to the quiz course part
  char label[100]; // Question label
  bool has_multiple_answers; // true if the question has multiple answers, false if it's a single answer
  int order; // Order of the question in the quiz

  char created_at[50]; // ISO 8601 format
  char updated_at[50]; // ISO 8601 format

  struct QuizQuestion *next; // Pointer to the next question in the list
  struct QuizQuestion *prev; // Pointer to the previous question in the list
};
typedef struct QuizQuestion QuizQuestion;

struct QuizQuestionList {
  QuizQuestion *head;
  int count;
};
typedef struct QuizQuestionList QuizQuestionList;

QueryResponseStatus get_quiz_questions_by_course_part_id(long course_part_id, QuizQuestionList **quiz_questions_list_ptr);

QuizQuestion* convert_mysql_fetched_row_to_quiz_question(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields);

void add_fetched_quiz_question_to_list(MYSQL_ROW quizRow, MYSQL_FIELD *fields, int num_fields, void **quiz_questions_list_ptr);

#endif //QUIZ_QUESTION_H
