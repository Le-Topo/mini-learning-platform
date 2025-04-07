//
// Created by astrid on 2025-04-07.
//

#ifndef QUIZ_ANSWER_SUGGESTION_H
#define QUIZ_ANSWER_SUGGESTION_H

#include <stdbool.h>

struct QuizAnswerSuggestion {
  long id;
  long question_id; // Foreign key to QuizQuestion
  char *label; // Answer label
  bool is_correct; // true if the answer is correct, false otherwise

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct QuizAnswerSuggestion QuizAnswerSuggestion;

#endif //QUIZ_ANSWER_SUGGESTION_H
