#ifndef COURSE_CONTROLLER_H
#define COURSE_CONTROLLER_H

#include "../../utils/enums/query-response-status.h"
#include "../../models/course.h"
#include "../../models/course-part.h"
#include "../../models/quiz-question.h"
#include "../../models/quiz-answer-suggestion.h"

QueryResponseStatus get_validated_courses(char *title, CourseList **courses_list_ptr);

QueryResponseStatus get_course_parts(long course_id, CoursePartList **course_parts_list_ptr);

QueryResponseStatus get_course_part_questions(long course_part_id, QuizQuestionList **quiz_questions_list_ptr);

QueryResponseStatus get_question_answers_suggestions(long question_id, QuizAnswerSuggestionList **quiz_answer_suggestions_list_ptr);

#endif //COURSE_CONTROLLER_H
