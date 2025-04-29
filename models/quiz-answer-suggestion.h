//
// Created by astrid on 2025-04-07.
//

#ifndef QUIZ_ANSWER_SUGGESTION_H
#define QUIZ_ANSWER_SUGGESTION_H

#include <stdbool.h>
#include "../utils/database/db-orm.h"
#include "../utils/enums/query-response-status.h"

#define QUIZ_ANSWER_SUGGESTIONS_TABLE "quiz_answer_suggestions"

struct QuizAnswerSuggestion {
  long id;
  long question_id; // Foreign key to QuizQuestion
  char label[100]; // Answer label
  bool is_correct; // true if the answer is correct, false otherwise

  char created_at[50]; // ISO 8601 format
  char updated_at[50]; // ISO 8601 format

  struct QuizAnswerSuggestion *next; // Pointer to the next suggestion in the list
  struct QuizAnswerSuggestion *prev; // Pointer to the previous suggestion in the list
};
typedef struct QuizAnswerSuggestion QuizAnswerSuggestion;

struct QuizAnswerSuggestionList {
  QuizAnswerSuggestion *head;
  int count;
};
typedef struct QuizAnswerSuggestionList QuizAnswerSuggestionList;

QueryResponseStatus get_quiz_answers_suggestions_by_question_id(long question_id, QuizAnswerSuggestionList **quiz_answer_suggestions_list_ptr);
QuizAnswerSuggestion* convert_mysql_fetched_row_to_quiz_answer_suggestion(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields);
void add_fetched_quiz_answer_suggestion_to_list(MYSQL_ROW quizRow, MYSQL_FIELD *fields, int num_fields, void **quiz_answer_suggestions_list_ptr);

#endif //QUIZ_ANSWER_SUGGESTION_H
