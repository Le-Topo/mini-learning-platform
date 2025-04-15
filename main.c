#include <stdio.h>
#include <mysql/mysql.h>
#include "utils/database/db-connection.h"
// #include "lib/pdcurses/include/curses.h"
// #include "lib/pdcurses/include/panel.h"
#include "views/welcome/welcome.view.h"
#include "views/auth/register/register.view.h"
#include "utils/curses/curses-utilities.h"
#include "routes/routes.h"
#include <stdbool.h>
#include <curses.h>

Route* add_route_to_execution_stack(Route *stack, const Route route, int *currentStackSize, int *currentRouteIndex) {

	if (currentStackSize == NULL) {
		log_message("Error: currentStackSize is NULL");
		exit(EXIT_FAILURE);
	}

	if (*currentStackSize == 0) {
		stack = (Route*)malloc(sizeof(Route));
		if (stack == NULL) {
			log_message("Error allocating memory for execution stack");
			exit(EXIT_FAILURE);
		}
	} else {
		Route *tmp = realloc(stack, sizeof(Route) * (*currentStackSize + 1));
		if (tmp == NULL) {
            log_message("Error reallocating memory for execution stack");
            exit(EXIT_FAILURE);
        }
		stack = tmp;
	}

	stack[*currentStackSize] = route;

	if (currentRouteIndex != NULL) {
		*currentRouteIndex = *currentStackSize;
	}

	(*currentStackSize)++;
	return stack;
}

int main(int argc, char *argv[]) {

	// This will be used to store execution stack (routes)
	Route *executionStack = NULL;
	int stackSize = 0, currentRouteIndex = 0;
	bool canExit = false;

	executionStack = add_route_to_execution_stack(executionStack, WELCOME, &stackSize, &currentRouteIndex);

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

    // Get the MySQL connection
    // MYSQL *conn = get_mysql_connection();

	int i = 1;
	while (!canExit) {
		Route nextRoute = EXIT;
		switch (executionStack[currentRouteIndex]) {
			case INSTRUCTOR_REGISTER:
				nextRoute = render_register_view(INSTRUCTOR);
				break;
			case INSTRUCTOR_LOGIN:
                nextRoute = EXIT;
                break;
			case LEARNER_REGISTER:
				nextRoute = EXIT;
			default:
				nextRoute = render_welcome_view();
		}

		executionStack = add_route_to_execution_stack(executionStack, nextRoute, &stackSize, &currentRouteIndex);
		canExit = nextRoute == EXIT;
	}

	free(executionStack);

	endwin();

    // mysql_close(conn);

    return EXIT_SUCCESS;
}
