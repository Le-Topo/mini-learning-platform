//
// Created by astri on 2025-04-09.
//

#ifndef NCURSES_UTILITIES_H
#define NCURSES_UTILITIES_H

// #include "../../lib/pdcurses/include/curses.h"
#include <curses.h>
#include <string.h>
#include <stdbool.h>
#include <form.h>
#include <stdlib.h>
#include "../../routes/routes.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MAX_WIN_LINES 40
#define MAX_WIN_COLS 140

#define NLINES 10
#define NCOLS 60

#define BLANK_LINE "                                                                 "
#define LONG_BLANK_LINE "                                                                                                        "

#define EXIT_KEY (KEY_F(12))
#define BACK_KEY (KEY_F(11))

#define DEFAULT_INPUT_WIDTH 33
#define DEFAULT_INPUT_HEIGHT 1
#define DEFAULT_INPUTS_SPACING_IN_A_ROW 4

typedef struct FieldProps {
    int height;
    int width;
    int starty;
    int startx;
    char *label;
    bool inlined_label;
} FieldProps;

typedef struct FieldsGroup {
    int fields_count;
    FieldProps *fields_props;
    FIELD **fields;
} FieldsGroup;

// This function is used to create a new panel/window
void init_wins(WINDOW **wins, int n);

// This function is used to display a panel/window
void win_show(WINDOW *win, char *label, int label_color);

// This function is used to print in horizontal middle of a window
void print_in_hmiddle_of_window(WINDOW *win, const int line, const int win_cols, const char *string);

void draw_rectangle(WINDOW *win, int x, int y, int width, int height);

void draw_rectangle_with_text(WINDOW *win, int *x, int *y, const char *text, int hpadding, int vpadding, bool should_print_in_whmiddle, int win_cols);

// param consider_h_keys is used to determine if the function should consider the horizontal keys (left and right arrows) or not
void handle_form_driver(FORM *form, int ch, bool consider_h_keys);

void free_fields(FIELD **fields, int num_fields);

void free_form_and_fields(FORM *form, FIELD **fields, int num_fields);

void free_form_and_fields_groups(FORM *form, FieldsGroup *fields_groups, int num_fields_groups);

FIELD** setup_fields(FieldProps *fields_props, int num_fields);

void attach_labels_to_fields(FIELD **fields, FieldProps *fields_props, int num_fields);

// This function is used to set the appropriate route based on the pressed key (F11 for back, F12 for exit)
void set_route_from_exit_keys(int pressed_key, Route *route);

#endif //NCURSES_UTILITIES_H
