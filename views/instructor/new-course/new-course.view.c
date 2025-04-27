//
// Created by astri on 2025-04-25.
//

#include "./new-course.view.h"

#define NEXT_STEP_KEY KEY_NPAGE
#define PREV_STEP_KEY KEY_PPAGE
#define SUBMIT_KEY KEY_F(10)

#define SECOND_INPUT_COLUMN_X (FREE_SPACE_START_X + DEFAULT_INPUT_WIDTH + DEFAULT_INPUTS_SPACING_IN_A_ROW + 1)
#define DOUBLE_WIDTH_INPUT (DEFAULT_INPUT_WIDTH * 2 + DEFAULT_INPUTS_SPACING_IN_A_ROW + 1)

static FieldProps coursePropertiesFieldsProps[] = {
  {1, DOUBLE_WIDTH_INPUT, FREE_SPACE_START_Y, FREE_SPACE_START_X, "Titre du cours", false},
  {2, DOUBLE_WIDTH_INPUT, FREE_SPACE_START_Y + 3, FREE_SPACE_START_X, "Description", false},
  {1, DEFAULT_INPUT_WIDTH, FREE_SPACE_START_Y + 7, FREE_SPACE_START_X, "Niveau (1, 2 ou 3)", false},
  {1, DEFAULT_INPUT_WIDTH, FREE_SPACE_START_Y + 7, SECOND_INPUT_COLUMN_X, "Duree (nombre d'heures necessaire)", false},
  {1, DOUBLE_WIDTH_INPUT, FREE_SPACE_START_Y + 10, FREE_SPACE_START_X, "Tags (separes par des virgules)", false},
};

Route render_instructor_new_course_view()
{
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
  clear();

  int ctrl = -1;
  const InstructorSidebarItem currentSidebarPage = INSTRUCTOR_NEW_COURSE;

  char *pageTitle = get_instructor_sidebar_item_name(currentSidebarPage);

  Route nextRoute = ROUTE_EXIT;
  //  bool shouldRefreshScreen = true;

  FieldsGroup *fieldsGroups = malloc(sizeof(FieldsGroup) * STEPS_COUNT);
  if (fieldsGroups == NULL) {
    log_message("Failed to allocate memory for allFields");
    exit(EXIT_FAILURE);
  }

  // Create the fields for each step
  for (int i = 0; i < STEPS_COUNT; i++) {
    int fieldsCount = 0;
    FieldProps *fieldsProps = get_new_course_form_fields_props(i, &fieldsCount);
    fieldsGroups[i].fields_count = fieldsCount;
    fieldsGroups[i].fields_props = fieldsProps;
    fieldsGroups[i].fields = setup_fields(fieldsProps, fieldsCount);
  }

  FORM *newCourseForm = NULL;
  int currentStep = NEW_COURSE_FORM_COURSE_PROPERTIES_STEP;
  Course course;
  CoursePart courseParts[] = {
      {
          .title = "Premier chapitre",
          .is_quiz = false,
          .content = "Bienvenue dans ce cours !",
          .order = 0,
      },
      {
          .title = "Deuxieme chapitre",
          .is_quiz = false,
          .content = "Voici le contenu du deuxieme chapitre.",
          .order = 1,
      },
      {
          .title = "Troisieme chapitre",
          .is_quiz = false,
          .content = "Voici le contenu du troisieme chapitre.",
          .order = 2,
      },

  };

  newCourseForm = new_form(fieldsGroups[currentStep].fields);
  post_form(newCourseForm);
  attach_labels_to_fields(fieldsGroups[currentStep].fields, fieldsGroups[currentStep].fields_props, fieldsGroups[currentStep].fields_count);

  render_instructor_sidebar(stdscr, currentSidebarPage);

  wattron(stdscr, COLOR_PAIR(5));
  mvwprintw(stdscr, MAX_WIN_LINES-2, 2, "Utiliser la touche F11 pour retourner a la page precedente et la touche F12 pour quitter");
  wattroff(stdscr, COLOR_PAIR(5));

  int submitButtonX, submitButtonY, nextButtonX, nextButtonY, prevButtonX, prevButtonY;
  prevButtonX = FREE_SPACE_START_X;
  prevButtonY = (MAX_WIN_LINES - 6);
  nextButtonX = MAX_WIN_COLS - 17;
  nextButtonY = prevButtonY;
  submitButtonX = (MAX_WIN_COLS - 20 + FREE_SPACE_START_X) / 2;
  submitButtonY = prevButtonY;
  draw_rectangle_with_text(stdscr, &nextButtonX, &nextButtonY, "[Page Down] Suivant", 2, 1, false, MAX_WIN_COLS);
  draw_rectangle_with_text(stdscr, &prevButtonX, &prevButtonY, "[Page Up] Precedent", 2, 1, false, MAX_WIN_COLS);
  draw_rectangle_with_text(stdscr, &submitButtonX, &submitButtonY, "[F10] Creer le cours", 2, 1, false, MAX_WIN_COLS);

  refresh();


  while (ctrl != EXIT_KEY && ctrl != BACK_KEY) {
    if (can_handle_pressed_key_in_sidebar(ctrl)) {
      nextRoute = get_instructor_page_route_from_key(ctrl);
      break;
    }

    switch(ctrl) {
      case NEXT_STEP_KEY:
        clear_screen();
        break;
      default:
        handle_form_driver(newCourseForm, ctrl, true);
        break;
    }

    ctrl = getch();
  }

  // Free the fields and form
  free_form_and_fields_groups(NULL, fieldsGroups, STEPS_COUNT);

  set_route_from_exit_keys(ctrl, &nextRoute);

  return nextRoute;
}

FieldProps *get_new_course_form_fields_props(NewCourseFormStep step, int *fieldsCount){
  const int secondInputColumnX = FREE_SPACE_START_X + DEFAULT_INPUT_WIDTH + DEFAULT_INPUTS_SPACING_IN_A_ROW + 1;

  switch (step) {
    case NEW_COURSE_FORM_COURSE_PROPERTIES_STEP:
      *fieldsCount = sizeof(coursePropertiesFieldsProps) / sizeof(FieldProps);
      return coursePropertiesFieldsProps;
    default:
      return NULL;
  }
}

void sync_course_properties_with_form(FIELD **fields, Course *course) {
  // Sync course properties with form fields
  FIELD *titleField = fields[0];
  FIELD *descriptionField = fields[1];
  FIELD *levelField = fields[2];
  FIELD *durationField = fields[3];
  FIELD *tagsField = fields[4];

//  course->title = strdup(field_buffer(titleField, 0));
//  course->description = strdup(field_buffer(descriptionField, 0));
//  course->level = atoi(field_buffer(levelField, 0));
//  course->duration = atoi(field_buffer(durationField, 0));
//  course->tags = strdup(field_buffer(tagsField, 0));
}

void sync_course_parts_properties_with_form(FIELD **fields, CoursePart *course_parts, int course_parts_count) {
  // Sync course parts properties with form fields
  for (int i = 0; i < course_parts_count; i++) {
    FIELD *titleField = fields[i * 2];
    FIELD *contentField = fields[i * 2 + 1];

    course_parts[i].title = strdup(field_buffer(titleField, 0));
    course_parts[i].content = strdup(field_buffer(contentField, 0));
  }
}

void setup_course_properties_form_validation(FIELD **fields) {
  // Setup validation for course properties form fields
  FIELD *titleField = fields[0];
  FIELD *descriptionField = fields[1];
  FIELD *levelField = fields[2];
  FIELD *durationField = fields[3];
  FIELD *tagsField = fields[4];

  set_field_type(titleField, TYPE_REGEXP, "[A-Za-z0-9._%+-]{1,}");
  set_field_type(fields[1], TYPE_ALNUM, 2);
  set_field_type(fields[2], TYPE_REGEXP, "[A-Za-z0-9._%+-]{1,20}+@[A-Za-z0-9.-]{1,20}+\\.[A-Za-z]{2,4}");
  set_field_type(fields[3], TYPE_ALNUM, 6);
  set_field_type(fields[4], TYPE_ALNUM, 6);
}

void clear_screen() {
  int availableLines = MAX_WIN_LINES - 5 - FREE_SPACE_START_Y;
  for (int i = 0; i < availableLines; i++) {
    mvwprintw(stdscr, i+FREE_SPACE_START_Y-1, FREE_SPACE_START_X, LONG_BLANK_LINE);
  }
  wrefresh(stdscr);
}