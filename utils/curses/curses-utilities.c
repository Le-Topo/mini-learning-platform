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

void handle_form_driver(FORM *form, int ch, bool consider_h_keys)
{
    if (ch == KEY_DOWN || (consider_h_keys && ch == KEY_RIGHT))
    {
        form_driver(form, REQ_NEXT_FIELD);
        form_driver(form, REQ_END_LINE);
    }
    else if (ch == KEY_UP || (consider_h_keys && ch == KEY_LEFT))
    {
        form_driver(form, REQ_PREV_FIELD);
        form_driver(form, REQ_END_LINE);
    }
    else if (ch == KEY_BACKSPACE || ch == KEY_DC || ch == 127) {
        form_driver(form, REQ_DEL_PREV);
    }
    else
    {
        form_driver(form, ch);
    }
}

void free_form_and_fields(FORM *form, FIELD **fields, int num_fields)
{
    // Unpost form and free the memory
    unpost_form(form);
    free_form(form);

    free_fields(fields, num_fields);
}

void free_fields(FIELD **fields, int num_fields)
{
    for (int i = 0; i < num_fields; i++)
    {
        if (fields[i] != NULL)
        {
            free_field(fields[i]);
        }
    }
    free(fields);
}

void free_form_and_fields_groups(FORM *form, FieldsGroup *fields_groups, int num_fields_groups)
{
    unpost_form(form);
    free_form(form);

    for (int i = 0; i < num_fields_groups; i++)
    {
        free_fields(fields_groups[i].fields, fields_groups[i].fields_count);
    }
    free(fields_groups);
}

FIELD** setup_fields(FieldProps *fields_props, int num_fields)
{
    FIELD **tmp = malloc((num_fields + 1) * sizeof(FIELD*));
    for (int i = 0; i < num_fields; i++)
    {
        int labelWidth = 0;
        if (fields_props[i].inlined_label)
        {
            labelWidth = (int) strlen(fields_props[i].label)+1;
        }

        tmp[i] = new_field(fields_props[i].height, fields_props[i].width, fields_props[i].starty, labelWidth + fields_props[i].startx, 0, 0);
        set_field_back(tmp[i], COLOR_PAIR(6)); // Print a line for the option
        field_opts_off(tmp[i], O_AUTOSKIP); // Don't go to next field when this field is filled up
        set_field_buffer(tmp[i], 1, fields_props[i].label);
    }
    tmp[num_fields] = NULL;

    return tmp;
    // form = new_form(fields);
    // post_form(form);

    // for (int i = 0; i < num_fields; i++)
    // {
    //     int labelX = fields_props[i].startx;
    //     int labelY = fields_props[i].starty - 1;
    //     if (fields_props[i].inlined_label)
    //     {
    //         labelX += fields_props[i].width + 1;
    //         labelY = fields_props[i].starty;
    //     }
    //     mvwprintw(stdscr, labelY, labelX, "%s", fields_props[i].label);
    // }

}

void attach_labels_to_fields(FIELD **fields, FieldProps *fields_props, int num_fields)
{
    for (int i = 0; i < num_fields; i++)
    {
        int labelX = fields_props[i].startx;
        int labelY = fields_props[i].starty - 1;
        if (fields_props[i].inlined_label)
        {
            labelY = fields_props[i].starty;
        }
        mvwprintw(stdscr, labelY, labelX, "%s", fields_props[i].label);
    }
}

void set_route_from_exit_keys(int pressed_key, Route *route) {
    if (pressed_key == BACK_KEY) {
        *route = ROUTE_BACK;
    } else if (pressed_key == EXIT_KEY) {
        *route = ROUTE_EXIT;
    }
}