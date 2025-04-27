//
// Created by astri on 2025-04-26.
//

#include "./courses.view.h"
#include "../../../controllers/course/course.controller.h"

#define SEARCH_BUTTON_KEY (KEY_F(10))

Route render_learner_courses_view()
{
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    clear();

    int ctrl = -1;
    const LearnerSidebarItem currentSidebarPage = LEARNER_COURSES;

    char *pageTitle = get_learner_sidebar_item_name(currentSidebarPage);

    Route nextRoute = ROUTE_EXIT;
    //    bool shouldRefreshScreen = true;

    FORM  *searchForm = NULL;
    FieldProps fields_props[] = {
        {1, 33, LEARNER_FREE_SPACE_START_Y-1, LEARNER_FREE_SPACE_START_X + 20, "Rechercher un cours : ", true},
    };
    FIELD **fields = setup_fields(fields_props, 1);
    searchForm = new_form(fields);
    post_form(searchForm);
    attach_labels_to_fields(fields, fields_props, 1);
    int searchButtonX = MAX_WIN_COLS - 17;
    int searchButtonY = fields_props[0].starty - 1;
    draw_rectangle_with_text(
        stdscr,
        &searchButtonX,
        &searchButtonY,
        "[F10] Rechercher",
        2,
        1,
        false,
        MAX_WIN_COLS
    );

    wattron(stdscr, COLOR_PAIR(5));
    mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a la page precedente et la touche F12 pour quitter");
    wattroff(stdscr, COLOR_PAIR(5));

    render_learner_sidebar(stdscr, currentSidebarPage);

    CourseList *pCoursesList = NULL;
    get_validated_courses("", &pCoursesList);
    Course *currentCourse = NULL;

    refresh();
    WINDOW *coursesListWindow = newwin(
        MAX_WIN_LINES - 15,
        MAX_WIN_COLS - LEARNER_SIDEBAR_WIDTH - 4,
        LEARNER_FREE_SPACE_START_Y+1,
        LEARNER_FREE_SPACE_START_X
    );
    refresh_courses_list(coursesListWindow, pCoursesList);

    while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
      if (can_handle_pressed_key_in_learner_sidebar(ctrl)) {
        nextRoute = get_learner_page_route_from_key(ctrl);
        break;
      }

      handle_form_driver(searchForm, ctrl, true);

      if (ctrl == SEARCH_BUTTON_KEY) {
        form_driver(searchForm, REQ_VALIDATION);

        if (pCoursesList != NULL) {
          currentCourse = pCoursesList->head;
          if (currentCourse != NULL) {
            while (currentCourse->next != NULL) {
                if (currentCourse->prev != NULL) {
                    free(currentCourse->prev);
                }
                currentCourse = currentCourse->next;
            }
            if (currentCourse != NULL) {
                free(currentCourse);
            }
          }
        }

        if (pCoursesList != NULL) {
          pCoursesList->head = NULL;
          pCoursesList->count = 0;
        }
        char *searchQuery = trim_whitespaces(field_buffer(fields[0], 0));
        get_validated_courses(searchQuery, &pCoursesList);
        refresh_courses_list(coursesListWindow, pCoursesList);
        form_driver(searchForm, REQ_VALIDATION);
      }

      ctrl = getch();
    }

    set_route_from_exit_keys(ctrl, &nextRoute);
    free(pCoursesList);
    return nextRoute;
}

void refresh_courses_list(WINDOW *win, CourseList *pCoursesList)
{
    wclear(win);
    if (pCoursesList == NULL) {
        mvwprintw(win, 0, 0, "Aucun cours trouve !");
        wrefresh(win);
        return;
    }

    Course *currentCourse = pCoursesList->head;
    int y = 0;
    int x = 0;

    if (currentCourse == NULL) {
      mvwprintw(win, 0, 0, "Aucun cours trouve !");
      wrefresh(win);
      return;
    }

    int i = 0, itemX = 0, itemY = 1;

    while (currentCourse != NULL) {
      mvwprintw(win, itemY, itemX, "[%d] %s", i + 1, currentCourse->title);

      int colorPair = get_course_level_color_pair(currentCourse->level);
      wattron(win, COLOR_PAIR(colorPair));
      mvwprintw(win, itemY, itemX + 55, "%s", get_course_level_name(currentCourse->level));
      wattroff(win, COLOR_PAIR(colorPair));

      mvwprintw(win, itemY, itemX + 75, "%dh", currentCourse->duration);

      //        mvhline(itemY+1, itemX, '-', MAX_WIN_COLS - itemX - 5);
      itemY += 3;
      i++;
      currentCourse = currentCourse->next;
    }

    wrefresh(win);
}