//
// Created by astri on 2025-04-28.
//

#define NEXT_PAGE_KEY KEY_NPAGE
#define PREV_PAGE_KEY KEY_PPAGE
#define START_COURSE_KEY KEY_F(10)

#include "./course-details.view.h"

Route render_course_details_view(Course course, WINDOW *win, int win_height, int win_width, const Route previous_route) {
    char pageTitle[20] = "Details du cours";
    int ctrl = -1;
    Route nextRoute = previous_route;

    change_page_title(stdscr, pageTitle);

    int courseDetailsX = 0;
    int courseDetailsY = 0;

    User instructor;
	memset(&instructor, 0, sizeof(User));
	get_instructor_by_id(course.instructor_id, &instructor);

	CoursePartList *pCoursePartsList = NULL;
	get_course_parts(course.id, &pCoursePartsList);

    wattron(win, A_BOLD);
    mvwprintw(win, courseDetailsY, courseDetailsX, "%s", "Titre du cours : ");
	mvwprintw(win, courseDetailsY + 2, courseDetailsX, "Description : ");
	mvwprintw(win, courseDetailsY + 4, courseDetailsX, "Instructeur : ");
	mvwprintw(win, courseDetailsY + 6, courseDetailsX, "Niveau : ");
	mvwprintw(win, courseDetailsY + 6, courseDetailsX+40, "Duree : ");
	mvwprintw(win, courseDetailsY + 8, courseDetailsX, "Tags : ");
	mvwprintw(win, courseDetailsY + 10, courseDetailsX, "Parties : ");
	wattroff(win, A_BOLD);

    mvwprintw(win, courseDetailsY, courseDetailsX + 20, "%s", course.title);
	mvwprintw(win, courseDetailsY + 2, courseDetailsX + 20, "%s", course.description);
	char instructorName[100];
	snprintf(instructorName, sizeof(instructorName), "%s %s", instructor.firstname, instructor.lastname);
	if (strlen(instructor.distinction) > 0) {
        strcat(instructorName, ", ");
        strcat(instructorName, instructor.distinction);
    }
	mvwprintw(win, courseDetailsY + 4, courseDetailsX + 20, "%s", instructorName);

	int colorPair = get_course_level_color_pair(course.level);
	wattron(win, COLOR_PAIR(colorPair));
	mvwprintw(win, courseDetailsY + 6, courseDetailsX + 20, "%s", get_course_level_name(course.level));
	wattroff(win, COLOR_PAIR(colorPair));

	mvwprintw(win, courseDetailsY + 6, courseDetailsX + 34, "||");
	mvwprintw(win, courseDetailsY + 6, courseDetailsX + 50, "%dh", course.duration);
	mvwprintw(win, courseDetailsY + 8, courseDetailsX + 20, "#%s", course.tags);

	CoursePart *currentCoursePart = pCoursePartsList->head;
	int i = 0;
	while (currentCoursePart != NULL) {
		char partTitle[100];
		strncpy(partTitle, currentCoursePart->title, sizeof(partTitle));
		if (currentCoursePart->is_quiz) {
			strcat(partTitle, " (?)");
		}
		mvwprintw(win, courseDetailsY + 10 + i, courseDetailsX + 20, "%d - %s", i+1, partTitle);
		currentCoursePart = currentCoursePart->next;
		i++;
	}

	int downloadButtonX = 0, downloadButtonY = 17;
	int startButtonX = 70, startButtonY = 17;

	draw_rectangle_with_text(win, &downloadButtonX, &downloadButtonY, "[F9] Telecharger le cours", 2, 1, false, win_width);
	draw_rectangle_with_text(win, &startButtonX, &startButtonY, "[F10] Commencer le cours", 2, 1, false, win_width);

    wrefresh(win);

	bool canGoToCourseFollowing = false;

    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
		if (can_handle_pressed_key_in_learner_sidebar(ctrl)) {
        	nextRoute = get_learner_page_route_from_key(ctrl);
        	break;
      	}

		if (ctrl == START_COURSE_KEY) {
			canGoToCourseFollowing = true;
			break;
		}

        ctrl = getch();
    }

	if (canGoToCourseFollowing) {
		nextRoute = handle_course_following(course, *pCoursePartsList, win, win_height, win_width, nextRoute);
	}

	free(pCoursePartsList);
    return nextRoute;
}

Route handle_course_following(const Course course, const CoursePartList course_parts_list, WINDOW *win, int win_height, int win_width, const Route previousRoute) {
	if (course_parts_list.head == NULL) {
		return previousRoute;
	}

	wclear(win);
	Route nextRoute = previousRoute;
	int ctrl = -1;

	change_page_title(stdscr, course.title);

	int courseDetailsX = 0;
	int courseDetailsY = 0;

	CoursePart *currentCoursePart = course_parts_list.head;
	QuizQuestionList *quizQuestionsList = NULL;
	QuizQuestion *currentQuestion = NULL;
	QuizAnswerSuggestionList *answerSuggestionsList = NULL;
	int currentCoursePartIndex = 0, currentQuestionIndex = 0;
	int i = 0;
	bool shouldRefreshScreen = true;
	bool shouldReinitQuiz = false;
	bool userHasAnsweredCurrentQuestion = false;
	int userAnswerIndex = -1;

	if (currentCoursePart->is_quiz) {
		get_course_part_questions(currentCoursePart->id, &quizQuestionsList);
		get_question_answers_suggestions(currentQuestion->id, &answerSuggestionsList);
		currentQuestion = quizQuestionsList->head;
	}

	wrefresh(win);

	while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
		if (can_handle_pressed_key_in_learner_sidebar(ctrl)) {
			nextRoute = get_learner_page_route_from_key(ctrl);
			break;
	  	}
		//mvwprintw(win, 16, 0, "%s", LONG_BLANK_LINE);
		//wrefresh(win);

		if (ctrl == NEXT_PAGE_KEY && currentCoursePart != NULL) {
			if (currentCoursePart->is_quiz) {
				if (currentQuestionIndex == (quizQuestionsList->count-1) && userHasAnsweredCurrentQuestion && currentCoursePart->next != NULL) {
					currentCoursePart = currentCoursePart->next;
					currentCoursePartIndex++;
					userHasAnsweredCurrentQuestion = false;
					shouldRefreshScreen = true;
				} else if (currentQuestionIndex < quizQuestionsList->count && userHasAnsweredCurrentQuestion) {
					currentQuestion = currentQuestion->next;
					currentQuestionIndex++;
					if (answerSuggestionsList != NULL) {
						free(answerSuggestionsList);
						answerSuggestionsList = NULL;
					}
					get_question_answers_suggestions(currentQuestion->id, &answerSuggestionsList);
					shouldRefreshScreen = true;
					userHasAnsweredCurrentQuestion = false;
				} else if (!userHasAnsweredCurrentQuestion) {
					wattron(win, COLOR_PAIR(1));
					mvwprintw(win, 16, 0, "Veuillez repondre a la question avant de continuer.");
					wattroff(win, COLOR_PAIR(1));
					wrefresh(win);
				}
			} else if (currentCoursePart->next != NULL) {
				currentCoursePart = currentCoursePart->next;
				currentCoursePartIndex++;
				userHasAnsweredCurrentQuestion = false;
				if (currentCoursePart->is_quiz) {
					shouldReinitQuiz = true;
				}
				shouldRefreshScreen = true;
			}

		} else if (ctrl == PREV_PAGE_KEY) {
			if (currentCoursePart->prev != NULL) {
				currentCoursePart = currentCoursePart->prev;
				currentCoursePartIndex--;
				currentQuestion = NULL;
				currentQuestionIndex = 0;
				shouldReinitQuiz = currentCoursePart->is_quiz;
				shouldRefreshScreen = true;
			}
		} else if (currentCoursePart->is_quiz && ctrl >= 'a' && ctrl <= ('a' + answerSuggestionsList->count - 1) && !userHasAnsweredCurrentQuestion) {
			if (currentQuestion != NULL && answerSuggestionsList != NULL) {
				userAnswerIndex = ctrl - 'a';
				userHasAnsweredCurrentQuestion = true;
				shouldRefreshScreen = true;
			}
		}
		if (shouldReinitQuiz) {
			if (quizQuestionsList != NULL) {
				free(quizQuestionsList);
				quizQuestionsList = NULL;
			}
			if (answerSuggestionsList != NULL) {
				free(answerSuggestionsList);
				answerSuggestionsList = NULL;
			}
			get_course_part_questions(currentCoursePart->id, &quizQuestionsList);
			currentQuestion = quizQuestionsList->head;
			get_question_answers_suggestions(currentQuestion->id, &answerSuggestionsList);
			currentQuestionIndex = 0;
			userHasAnsweredCurrentQuestion = false;
			shouldReinitQuiz = false;
			shouldRefreshScreen = true;
		}

		if (shouldRefreshScreen) {
			refresh_course_following_page(
				win,
				currentCoursePart,
				currentCoursePartIndex,
				course_parts_list.count,
				currentQuestion,
				currentQuestionIndex,
				answerSuggestionsList,
				userHasAnsweredCurrentQuestion,
				userAnswerIndex
			);
			shouldRefreshScreen = false;
		}

		ctrl = getch();
	}

	return nextRoute;
}

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
) {
	wclear(win);

	wattron(win, A_BOLD);
	mvwprintw(win, 0, 0, "%d - %s", currentCoursePartIndex+1, currentCoursePart->title);
	mvwprintw(win, 0, 70, "Progession: %d%%", (currentCoursePartIndex * 100) / coursePartsCount);
	wattroff(win, A_BOLD);

	if (!currentCoursePart->is_quiz) {
		mvwprintw(win, 2, 0, "%s", currentCoursePart->content);
	} else {
		mvwprintw(win, 2, 0, "Question %d : %s", currentQuestionIndex+1, currentQuestion->label);
		QuizAnswerSuggestion *currentAnswer = answerSuggestionsList->head;
		log_message("User has answered question: %d from index %d", userHasAnsweredCurrentQuestion, userAnswerIndex);
		for (int i = 0; i < answerSuggestionsList->count && currentAnswer != NULL; i++) {
			if (userHasAnsweredCurrentQuestion && i == userAnswerIndex) {
				int colorPair = currentAnswer->is_correct ? 2 : 1;
				wattron(win, COLOR_PAIR(colorPair));
				mvwprintw(win, 4 + i, 0, "%c) - %s *", 'a'+i, currentAnswer->label);
				wattroff(win, COLOR_PAIR(colorPair));
			} else if (userHasAnsweredCurrentQuestion && currentAnswer->is_correct) {
				wattron(win, COLOR_PAIR(2));
				mvwprintw(win, 4 + i, 0, "%c) - %s", 'a'+i, currentAnswer->label);
				wattroff(win, COLOR_PAIR(2));
			} else if (userHasAnsweredCurrentQuestion) {
				mvwprintw(win, 4 + i, 0, "%c) - %s", 'a'+i, currentAnswer->label);
			} else {
				mvwprintw(win, 4 + i, 0, "[%c] - %s", 'a'+i, currentAnswer->label);
			}

			currentAnswer = currentAnswer->next;
		}
		if (userHasAnsweredCurrentQuestion) {
			mvwprintw(win, 4 + answerSuggestionsList->count, 0, "Vous avez repondu: %c", 'a' + userAnswerIndex);
		}
	}

	int prevButtonX = 0, prevButtonY = 17;
	int nextButtonX = 70, nextButtonY = 17;

	if (currentCoursePart->prev != NULL) {
		draw_rectangle_with_text(win, &prevButtonX, &prevButtonY, "[Page Up] Precedent", 2, 1, false, 0);
	}
	if (currentCoursePart->next != NULL) {
		draw_rectangle_with_text(win, &nextButtonX, &nextButtonY, "[Page Down] Suivant", 2, 1, false, 0);
	} else {
		draw_rectangle_with_text(win, &nextButtonX, &nextButtonY, "[F10] Terminer le cours", 2, 1, false, 0);
	}

	wrefresh(win);
}