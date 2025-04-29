//
// Created by astri on 2025-04-26.
//
#include "./course.controller.h"

QueryResponseStatus get_validated_courses(char *title, CourseList **courses_list_ptr) {
  return get_courses(title, true, courses_list_ptr);
}

QueryResponseStatus get_course_parts(long course_id, CoursePartList **course_parts_list_ptr) {
  return get_course_parts_by_course_id(course_id, course_parts_list_ptr);
}

QueryResponseStatus get_course_part_questions(long course_part_id, QuizQuestionList **quiz_questions_list_ptr) {
  return get_quiz_questions_by_course_part_id(course_part_id, quiz_questions_list_ptr);
}

QueryResponseStatus get_question_answers_suggestions(long question_id, QuizAnswerSuggestionList **quiz_answer_suggestions_list_ptr) {
  return get_quiz_answers_suggestions_by_question_id(question_id, quiz_answer_suggestions_list_ptr);
}
