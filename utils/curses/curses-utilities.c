//
// Created by astri on 2025-04-09.
//

#include "./curses-utilities.h"

/* Put all the windows */
void init_wins(WINDOW **wins, int n)
{	int x, y, i;
    char label[80];

    y = 2;
    x = 10;
    for(i = 0; i < n; ++i)
    {	wins[i] = newwin(NLINES, NCOLS, y, x);
        sprintf(label, "Window Number %d", i + 1);
        win_show(wins[i], label, i + 1);
        y += 3;
        x += 7;
    }
}

/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

    getbegyx(win, starty, startx);
    getmaxyx(win, height, width);

    box(win, 0, 0);
    mvwaddch(win, 2, 0, ACS_LTEE);
    mvwhline(win, 2, 1, ACS_HLINE, width - 2);
    mvwaddch(win, 2, width - 1, ACS_RTEE);

    // print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_hmiddle_of_window(WINDOW *win, const int line, const int win_cols, const char *string)
{
    const int str_length = strlen(string);
    const int startx = (win_cols - str_length) / 2;

    mvwprintw(win, line, startx, "%s", string);
}

void draw_rectangle(WINDOW *win, int x, int y, int width, int height)
{
    if (win == NULL)
        win = stdscr;

    mvwaddch(win, y, x, ACS_ULCORNER);
    mvwaddch(win, y, x + width, ACS_URCORNER);
    mvwaddch(win, y + height, x, ACS_LLCORNER);
    mvwaddch(win, y + height, x + width, ACS_LRCORNER);
    mvwhline(win, y, x + 1, 0, width - 1);
    mvwhline(win, y + height, x + 1, 0, width - 1);
    mvwvline(win, y + 1, x, 0, height - 1);
    mvwvline(win, y + 1, x + width, 0, height - 1);
    // mvwprintw(win, y, x, "a");
    // mvwprintw(win, x, y, "b");
    // mvwhline(win, x, y, width, 0);
    // mvwvline(win, x, y, 0, width);
    // mvwhline(win, x + height - 1, y, 0, width);
    // mvwvline(win, x, y + width - 1, 0, height);
}

void draw_rectangle_with_text(WINDOW *win, int *x, int *y, const char *text, int hpadding, int vpadding, bool should_print_in_whmiddle, int win_cols)
{
    int width = strlen(text) + 2 * hpadding; // Width of the rectangle, including padding
    const int height = vpadding * 2; // Height of the rectangle, including padding

    if (should_print_in_whmiddle)
        *x = (win_cols - width) / 2;
    draw_rectangle(win, *x, *y, width, height);
    mvwprintw(win, *y+vpadding, *x+hpadding, "%s", text);
    wrefresh(win);
    *y += height; // Move the y position down for the next rectangle
    *x += width;
}