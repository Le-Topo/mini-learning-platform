//
// Created by astri on 2025-04-09.
//

#ifndef NCURSES_UTILITIES_H
#define NCURSES_UTILITIES_H

// #include "../../lib/pdcurses/include/curses.h"
#include <curses.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define MAX_WIN_LINES 40
#define MAX_WIN_COLS 140

#define NLINES 10
#define NCOLS 60

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs,
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

struct _PANEL_DATA {
    bool hide;	/* true if panel is hidden */
};
typedef struct _PANEL_DATA PANEL_DATA;

// This function is used to create a new panel/window
void init_wins(WINDOW **wins, int n);

// This function is used to display a panel/window
void win_show(WINDOW *win, char *label, int label_color);

// This function is used to print in horizontal middle of a window
void print_in_hmiddle_of_window(WINDOW *win, const int line, const int win_cols, const char *string);

void draw_rectangle(WINDOW *win, int x, int y, int width, int height);

void draw_rectangle_with_text(WINDOW *win, int *x, int *y, const char *text, int hpadding, int vpadding, bool should_print_in_whmiddle, int win_cols);

#endif //NCURSES_UTILITIES_H
