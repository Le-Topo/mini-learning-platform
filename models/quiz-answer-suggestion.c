//
// Created by astri on 2025-04-29.
//

#include "./quiz-answer-suggestion.h"

QueryResponseStatus get_quiz_answers_suggestions_by_question_id(long question_id, QuizAnswerSuggestionList **quiz_answer_suggestions_list_ptr) {
    MYSQL *conn = get_mysql_connection();

    char whereClause[80];
    snprintf(whereClause, sizeof(whereClause), "WHERE question_id = %ld", question_id);

    QuizAnswerSuggestion quiz_answer_suggestion;
    memset(&quiz_answer_suggestion, 0, sizeof(QuizAnswerSuggestion));

    QueryResponseStatus status = select_from_table(
        conn,
        QUIZ_ANSWER_SUGGESTIONS_TABLE,
        "*",
        whereClause,
        add_fetched_quiz_answer_suggestion_to_list,
        (void **)quiz_answer_suggestions_list_ptr
    );

    return status;
}

void add_fetched_quiz_answer_suggestion_to_list(MYSQL_ROW quizRow, MYSQL_FIELD *fields, int num_fields, void **quiz_answer_suggestions_list_ptr) {
    QuizAnswerSuggestion *quiz_answer_suggestion = convert_mysql_fetched_row_to_quiz_answer_suggestion(quizRow, fields, num_fields);
    quiz_answer_suggestion->next = NULL;
    quiz_answer_suggestion->prev = NULL;

    QuizAnswerSuggestionList **list_ptr = (QuizAnswerSuggestionList **)quiz_answer_suggestions_list_ptr;

    if (*list_ptr == NULL) {
        *list_ptr = calloc(1, sizeof(QuizAnswerSuggestionList));
    }

    QuizAnswerSuggestionList *list = *list_ptr;

    if (list->head == NULL) {
        list->head = quiz_answer_suggestion;
        list->count = 1;
    } else {
        QuizAnswerSuggestion *p = list->head;

        while (p->next) p = p->next;

        quiz_answer_suggestion->prev = p;
        p->next = quiz_answer_suggestion;
        list->count++;
    }

    log_message("Added quiz answer suggestion: %s %d", quiz_answer_suggestion->label, list->count);
}

QuizAnswerSuggestion* convert_mysql_fetched_row_to_quiz_answer_suggestion(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields) {
    QuizAnswerSuggestion *quiz_answer_suggestion = calloc(1, sizeof(QuizAnswerSuggestion));
    if (quiz_answer_suggestion == NULL) {
        log_message("Failed to allocate memory for QuizAnswerSuggestion");
        return NULL;
    }

    for (int i = 0; i < num_fields; i++) {
        const char *name = fields[i].name;
        const char *value = row[i];

        if (strcmp(name, "id") == 0) {
            quiz_answer_suggestion->id = atol(value);
        } else if (strcmp(name, "question_id") == 0) {
            quiz_answer_suggestion->question_id = atol(value);
        } else if (strcmp(name, "label") == 0) {
            strncpy(quiz_answer_suggestion->label, value, sizeof(quiz_answer_suggestion->label));
        } else if (strcmp(name, "is_correct") == 0) {
            quiz_answer_suggestion->is_correct = atoi(value);
        } else if (strcmp(name, "created_at") == 0) {
            strncpy(quiz_answer_suggestion->created_at, value, sizeof(quiz_answer_suggestion->created_at));
        } else if (strcmp(name, "updated_at") == 0) {
            strncpy(quiz_answer_suggestion->updated_at, value, sizeof(quiz_answer_suggestion->updated_at));
        }
    }

    return quiz_answer_suggestion;
}