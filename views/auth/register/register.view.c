//
// Created by astri on 2025-04-09.
//

#include "./register.view.h"

#define FIELDS_COUNT 5
#define SUBMIT_KEY (KEY_F(1))

Route render_register_view(UserRole user_role) {
    // WINDOW *registerWindow = newwin(MAX_WIN_LINES, MAX_WIN_COLS, 1, 1);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    clear();

    int ctrl = 0;
    char pageTitle[30];
    sprintf(pageTitle, "Inscription (%s)", get_user_role_description(user_role));
    Route nextRoute = EXIT;
    bool shouldRefreshScreen = true;

    FORM  *registerForm = NULL;
    FieldProps fields_props[] = {
        {1, 33, 8, 34, "Prenom", false},
        {1, 33, 8, 72, "Nom", false},
        {1, 71, 11, 34, "Email", false},
        {1, 33, 14, 34, "Mot de passe", false},
        {1, 33, 14, 72, "Confirmer mot de passe", false}
    };
    FIELD **fields = setup_fields(fields_props, FIELDS_COUNT);

    set_field_type(fields[0], TYPE_ALNUM, 2);
    set_field_type(fields[1], TYPE_ALNUM, 2);
    set_field_type(fields[2], TYPE_REGEXP, "[A-Za-z0-9._%+-]{1,20}+@[A-Za-z0-9.-]{1,20}+\\.[A-Za-z]{2,4}");
    set_field_type(fields[3], TYPE_ALNUM, 6);
    set_field_type(fields[4], TYPE_ALNUM, 6);

    registerForm = new_form(fields);
    post_form(registerForm);
    attach_labels_to_fields(fields, fields_props, FIELDS_COUNT);

    // WINDOW *registerFormWindow = form_win(registerForm);
    WINDOW *errorsWindow = newwin(3, 3, 3, 3);
    box(errorsWindow, 0, 0);
    wrefresh(errorsWindow);

    wattron(stdscr, COLOR_PAIR(5));
    mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a l'accueil et la touche F12 pour quitter");
    wattroff(stdscr, COLOR_PAIR(5));

    print_in_hmiddle_of_window(stdscr, 2, MAX_WIN_COLS, pageTitle);
    draw_rectangle(stdscr, 30, 4, 78, 16);

    int submitButtonX = 3, submitButtonY = 16;
    draw_rectangle_with_text(stdscr, &submitButtonX, &submitButtonY, "[F1] Soumettre", 2, 1, true, MAX_WIN_COLS);

    move(fields_props[0].starty, fields_props[0].startx);
    post_form(registerForm);
    refresh();

    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
        mvprintw(22, 34, BLANK_LINE);
        mvprintw(23, 34, BLANK_LINE);
        mvprintw(24, 34, BLANK_LINE);
        mvprintw( 25, 34, BLANK_LINE);
        mvprintw(19, 34, BLANK_LINE);

        handle_form_driver(registerForm, ctrl, true);

        if (ctrl == SUBMIT_KEY) { // Submit button pressed
            int formIsInvalid = form_driver(registerForm, REQ_VALIDATION) != E_OK;
            bool someFieldIsEmpty = false;
            for (int i = 0; i < FIELDS_COUNT; i++) {
                if (strlen(trim_whitespaces(field_buffer(fields[i], 0))) == 0) {
                    someFieldIsEmpty = true;
                    break;
                }
            }
            // bool passwordsMatch = strcmp(field_buffer(fields[3], 0), field_buffer(fields[4], 0)) == 0;

            if (formIsInvalid || someFieldIsEmpty) {
                wattron(stdscr, COLOR_PAIR(1));
                print_in_hmiddle_of_window(stdscr, 19, MAX_WIN_COLS, "Formulaire invalide !");
                wattroff(stdscr, COLOR_PAIR(1));

                mvprintw(22, 34, "- Le nom et le prenom doivent contenir au moins 2 caracteres");
                mvprintw(23, 34, "- L'email doit etre valide");
                mvprintw(24, 34, "- Le mot de passe doit contenir au moins 6 caracteres");
                mvprintw(25, 34, "- Les mots de passe doivent correspondre");

                // move(fields_props[0].starty, fields_props[0].startx);
            } else {
                const char *firstname = field_buffer(fields[0], 0);
                const char *lastname = field_buffer(fields[1], 0);
                const char *email = field_buffer(fields[2], 0);
                const char *password = field_buffer(fields[3], 0);

                register_user(
                    trim_whitespaces((char *)email),
                    trim_whitespaces((char *)password),
                    trim_whitespaces((char *)firstname),
                    trim_whitespaces((char *)lastname),
                    user_role
                );
            }
        }

        refresh();
        ctrl = getch();
    }

    free_form_and_fields(registerForm, fields, FIELDS_COUNT);

    if (ctrl == BACK_KEY) {
        nextRoute = BACK;
    }

    return nextRoute;
}