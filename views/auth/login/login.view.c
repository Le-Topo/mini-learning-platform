//
// Created by astri on 2025-04-17.
//

#include "./login.view.h"

#define FIELDS_COUNT 2
#define SUBMIT_KEY (KEY_F(10))

Route render_login_view(UserRole user_role) {
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    clear();

    int ctrl = 0;
    char pageTitle[30];
    sprintf(pageTitle, "Connexion (%s)", get_user_role_description(user_role));
    Route nextRoute = ROUTE_EXIT;
    bool shouldRefreshScreen = true;

    FORM *loginForm = NULL;
    FieldProps fields_props[] = {
        {1, 56, 9, 41, "Email", false},
        {1, 56, 12, 41, "Mot de passe", false},
    };
    FIELD **fields = setup_fields(fields_props, FIELDS_COUNT);

    set_field_type(fields[0], TYPE_REGEXP, "[A-Za-z0-9._%+-]{1,20}+@[A-Za-z0-9.-]{1,20}+\\.[A-Za-z]{2,4}");
    set_field_type(fields[1], TYPE_ALNUM, 6);

    loginForm = new_form(fields);
    post_form(loginForm);
    attach_labels_to_fields(fields, fields_props, FIELDS_COUNT);

    wattron(stdscr, COLOR_PAIR(5));
    mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a l'accueil et la touche F12 pour quitter");
    wattroff(stdscr, COLOR_PAIR(5));

    print_in_hmiddle_of_window(stdscr, 2, MAX_WIN_COLS, pageTitle);
    draw_rectangle(stdscr, 30, 4, 78, 16);

    int submitButtonX = 3, submitButtonY = 16;
    draw_rectangle_with_text(stdscr, &submitButtonX, &submitButtonY, "[F10] Soumettre", 2, 1, true, MAX_WIN_COLS);

    refresh();

    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
        mvprintw(22, 34, BLANK_LINE);
        mvprintw(23, 34, BLANK_LINE);
        mvprintw(24, 34, BLANK_LINE);
        mvprintw( 25, 34, BLANK_LINE);
        mvprintw(19, 34, BLANK_LINE);

        handle_form_driver(loginForm, ctrl, true);

        if (ctrl == SUBMIT_KEY) { // Submit button pressed
            int formIsInvalid = form_driver(loginForm, REQ_VALIDATION) != E_OK;
            bool someFieldIsEmpty = false;
            for (int i = 0; i < FIELDS_COUNT; i++) {
                if (strlen(trim_whitespaces(field_buffer(fields[i], 0))) == 0) {
                    someFieldIsEmpty = true;
                    break;
                }
            }

            if (formIsInvalid || someFieldIsEmpty) {
                wattron(stdscr, COLOR_PAIR(1));
                print_in_hmiddle_of_window(stdscr, 19, MAX_WIN_COLS, "Formulaire invalide !");
                wattroff(stdscr, COLOR_PAIR(1));

                mvprintw(22, 34, "- L'email doit etre valide");
                mvprintw(23, 34, "- Le mot de passe doit contenir au moins 6 caracteres");
            } else {
                const char *password = field_buffer(fields[0], 0);
                const char *email = field_buffer(fields[1], 0);

//                register_user(
//                    trim_whitespaces((char *)email),
//                    trim_whitespaces((char *)password),
//                    trim_whitespaces((char *)firstname),
//                    trim_whitespaces((char *)lastname),
//                    user_role
//                );
                mvprintw(23, 34, "Enregistrement de l'utilisateur...");
            }
        }

        refresh();
        ctrl = getch();
    }

    free_form_and_fields(loginForm, fields, FIELDS_COUNT);

    if (ctrl == BACK_KEY) {
        nextRoute = ROUTE_BACK;
    }

    return nextRoute;
}