//
// Created by astri on 2025-04-18.
//

#include "./routes.h"

Route* add_route_to_execution_stack(Route *stack, const Route route, int *currentStackSize, int *currentRouteIndex) {

    if (currentStackSize == NULL || *currentStackSize < 0) {
        log_message("Error: currentStackSize is NULL or negative");
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