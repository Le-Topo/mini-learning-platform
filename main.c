#include <stdio.h>
#include <mysql/mysql.h>
#include "routes/routes.h"
#include <stdbool.h>
#include <curses.h>
#include "utils/database/db-connection.h"
// #include "lib/pdcurses/include/curses.h"
// #include "lib/pdcurses/include/panel.h"
#include "views/welcome/welcome.view.h"
#include "views/auth/register/register.view.h"
#include "views/auth/login/login.view.h"
#include "views/instructor/dashboard/dashboard.view.h"
#include "utils/curses/curses-utilities.h"
#include "views/instructor/new-course/new-course.view.h"
#include "views/learner/dashboard/dashboard.view.h"
#include "views/learner/courses/courses.view.h"
#include "utils/session-handler/session-handler.h"

void process_user_logout(Route *stack, int *currentStackSize, int *currentRouteIndex) {
	free(stack);
	stack = NULL;
	*currentStackSize = 0;
	*currentRouteIndex = 0;
	destroy_session();
}

int main(int argc, char *argv[]) {

	// This will be used to store execution stack (routes)
	Route *executionStack = NULL;
	int stackSize = 0, currentRouteIndex = 0;
	bool canExit = false;

	executionStack = add_route_to_execution_stack(executionStack, ROUTE_LEARNER_COURSES, &stackSize, &currentRouteIndex);

	/* Initialize curses */
	initscr();
	// resize_term(MAX_WIN_LINES+2, MAX_WIN_COLS+2);
	start_color();

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_BLACK, COLOR_WHITE);

    // Get the MySQL connection
    MYSQL *conn = get_mysql_connection();

	while (!canExit) {
		Route nextRoute = ROUTE_EXIT;
		switch (executionStack[currentRouteIndex]) {
			case ROUTE_INSTRUCTOR_REGISTER:
				nextRoute = render_register_view(INSTRUCTOR);
				break;
			case ROUTE_INSTRUCTOR_LOGIN:
                nextRoute = render_login_view(INSTRUCTOR);
                break;
			case ROUTE_INSTRUCTOR_DASHBOARD:
				nextRoute = render_instructor_dashboard_view();
				break;
			case ROUTE_INSTRUCTOR_NEW_COURSE:
				nextRoute = render_instructor_new_course_view();
				break;

			case ROUTE_LEARNER_REGISTER:
				nextRoute = render_register_view(LEARNER);
				break;
			case ROUTE_LEARNER_LOGIN:
				nextRoute = render_login_view(LEARNER);
				break;
			case ROUTE_LEARNER_DASHBOARD:
				nextRoute = render_learner_dashboard_view();
				break;
			case ROUTE_LEARNER_COURSES:
				nextRoute = render_learner_courses_view();
				break;

			case ROUTE_LOGOUT:
				process_user_logout(executionStack, &stackSize, &currentRouteIndex);
				nextRoute = ROUTE_WELCOME;
				break;
			default:
				nextRoute = render_welcome_view();
		}

		if (nextRoute == ROUTE_BACK) {
			if (stackSize > 1) {
				currentRouteIndex--;
				stackSize--;
				nextRoute = executionStack[currentRouteIndex];
			} else {
				nextRoute = ROUTE_EXIT;
			}
		} else {
			executionStack = add_route_to_execution_stack(executionStack, nextRoute, &stackSize, &currentRouteIndex);
		}
		canExit = nextRoute == ROUTE_EXIT;
	}

	free(executionStack);

	endwin();

    mysql_close(conn);

    return EXIT_SUCCESS;
}
