//
// Created by astri on 2025-04-29.
//

#include "./quiz-question.h"

QueryResponseStatus get_quiz_questions_by_course_part_id(long course_part_id, QuizQuestionList **quiz_questions_list_ptr) {
    MYSQL *conn = get_mysql_connection();

    char whereClause[80];
    snprintf(whereClause, sizeof(whereClause), "WHERE course_part_id = %ld", course_part_id);

    QuizQuestion quiz_question;
    memset(&quiz_question, 0, sizeof(QuizQuestion));

    QueryResponseStatus status = select_from_table(
        conn,
        QUIZ_QUESTIONS_TABLE,
        "*",
        whereClause,
        add_fetched_quiz_question_to_list,
        (void **)quiz_questions_list_ptr
    );

    return status;
}

void add_fetched_quiz_question_to_list(MYSQL_ROW quizRow, MYSQL_FIELD *fields, int num_fields, void **quiz_questions_list_ptr) {
    QuizQuestion *quiz_question = convert_mysql_fetched_row_to_quiz_question(quizRow, fields, num_fields);
    quiz_question->next = NULL;
    quiz_question->prev = NULL;

    QuizQuestionList **list_ptr = (QuizQuestionList **)quiz_questions_list_ptr;

    if (*list_ptr == NULL) {
        *list_ptr = calloc(1, sizeof(QuizQuestionList));
    }

    QuizQuestionList *list = *list_ptr;

    if (list->head == NULL) {
        list->head = quiz_question;
        list->count = 1;
    } else {
        QuizQuestion *p = list->head;

        while (p->next) p = p->next;

        quiz_question->prev = p;
        p->next = quiz_question;
        list->count++;
    }

    log_message("Added quiz question: %s %d", quiz_question->label, list->count);
}

QuizQuestion* convert_mysql_fetched_row_to_quiz_question(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields) {
    QuizQuestion *quiz_question = calloc(1, sizeof(QuizQuestion));
    if (quiz_question == NULL) {
        log_message("Failed to allocate memory for QuizQuestion");
        return NULL;
    }

    for (int i = 0; i < num_fields; i++) {
        const char *name = fields[i].name;
        const char *value = row[i];

        if (strcmp(name, "id") == 0) {
            quiz_question->id = atol(value);
        } else if (strcmp(name, "course_part_id") == 0) {
            quiz_question->course_part_id = atol(value);
        } else if (strcmp(name, "label") == 0) {
            strncpy(quiz_question->label, value, sizeof(quiz_question->label));
        } else if (strcmp(name, "has_multiple_answers") == 0) {
            quiz_question->has_multiple_answers = atoi(value);
        } else if (strcmp(name, "order") == 0) {
            quiz_question->order = atoi(value);
        } else if (strcmp(name, "created_at") == 0) {
            strncpy(quiz_question->created_at, value, sizeof(quiz_question->created_at));
        } else if (strcmp(name, "updated_at") == 0) {
            strncpy(quiz_question->updated_at, value, sizeof(quiz_question->updated_at));
        }
    }

    return quiz_question;
}
