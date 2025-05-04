//
// Created by astrid on 2025-04-28.
//

#ifndef COURSE_DETAILS_VIEW_H
#define COURSE_DETAILS_VIEW_H

#include <curses.h>
#include "../../../utils/curses/curses-utilities.h"
#include "../../../models/course.h"
#include "../../../models/course-part.h"
#include "../../../models/quiz-question.h"
#include "../../../models/quiz-answer-suggestion.h"
#include "../learner.layout.h"
#include "../../../controllers/instructor/instructor.controller.h"
#include "../../../controllers/course/course.controller.h"


Route render_course_details_view(Course course, WINDOW *win, int win_height, int win_width, const Route previous_route);

Route handle_course_following(const Course course, const CoursePartList course_parts_list, WINDOW *win, int win_height, int win_width, const Route previousRoute);

void refresh_course_following_page(
    WINDOW *win,
    CoursePart *currentCoursePart,
    int currentCoursePartIndex,
    int coursePartsCount,
    QuizQuestion *currentQuestion,
    int currentQuestionIndex,
    QuizAnswerSuggestionList *answerSuggestionsList,
    bool userHasAnsweredCurrentQuestion,
    int userAnswerIndex
);

#endif //COURSE_DETAILS_VIEW_H
