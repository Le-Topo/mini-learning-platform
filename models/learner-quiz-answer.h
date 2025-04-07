//
// Created by astrid on 2025-04-07.
//

#ifndef LEARNER_QUIZ_ANSWER_H
#define LEARNER_QUIZ_ANSWER_H

#include <stdbool.h>

struct LearnerQuizAnswer {
  long id;
  long learner_id; // Foreign key to User
  long question_id; // Foreign key to QuizQuestion
  long answer_id; // Foreign key to QuizAnswerSuggestion
  bool is_correct; // true if the answer is correct, false otherwise

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct LearnerQuizAnswer LearnerQuizAnswer;

#endif //LEARNER_QUIZ_ANSWER_H
