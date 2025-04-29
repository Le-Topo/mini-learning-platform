//
// Created by astri on 2025-04-26.
//

#include "./course.h"

QueryResponseStatus get_courses(char *title, bool validated, CourseList **course_list_ptr) {
    MYSQL *conn = get_mysql_connection();

    char whereClause[80];
    snprintf(whereClause, sizeof(whereClause), "WHERE is_validated = %d AND title LIKE ", validated);
    strcat(whereClause, "'%");
    strcat(whereClause, title);
    strcat(whereClause, "%'");

    Course course;
    memset(&course, 0, sizeof(Course));

    QueryResponseStatus status = select_from_table(
        conn,
        COURSES_TABLE,
        "*",
        whereClause,
        add_fetched_course_to_list,
        (void **)course_list_ptr
    );

    return status;
}

void add_fetched_course_to_list(MYSQL_ROW courseRow, MYSQL_FIELD *fields, int num_fields, void **course_list_ptr) {
    Course *course = convert_mysql_fetched_row_to_course(courseRow, fields, num_fields);
    course->next = NULL;
    course->prev = NULL;

    CourseList **list_ptr = (CourseList **)course_list_ptr;

    if (*list_ptr == NULL) {
        *list_ptr = calloc(1, sizeof(CourseList));
    }

    CourseList *list = *list_ptr;

    if (list->head == NULL) {
        list->head = course;
        list->count = 1;
    } else {
        Course *p = list->head;

        while (p->next) p = p->next;

        course->prev = p;
        p->next = course;
        list->count++;
    }

    log_message("Added course: %s %d", course->title, list->count);
}

Course* convert_mysql_fetched_row_to_course(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields) {
    Course *c = calloc(1, sizeof(Course));
    if (!c) return NULL;

    for (int i = 0; i < num_fields; i++) {
        const char *name = fields[i].name;
        const char *value = row[i];

        if (!value) continue;

        if (strcmp(name, "id") == 0) c->id = atol(value);
        else if (strcmp(name, "instructor_id") == 0) c->instructor_id = atol(value);
        else if (strcmp(name, "title") == 0) strncpy(c->title, value, sizeof(c->title));
        else if (strcmp(name, "description") == 0) strncpy(c->description, value, sizeof(c->description));
        else if (strcmp(name, "level") == 0) c->level = atoi(value);
        else if (strcmp(name, "duration") == 0) c->duration = atoi(value);
        else if (strcmp(name, "tags") == 0) strncpy(c->tags, value, sizeof(c->tags));
        else if (strcmp(name, "is_validated") == 0) c->is_validated = atoi(value);
        else if (strcmp(name, "validation_message") == 0) strncpy(c->validation_message, value, sizeof(c->validation_message));
        else if (strcmp(name, "created_at") == 0) strncpy(c->created_at, value, sizeof(c->created_at));
        else if (strcmp(name, "updated_at") == 0) strncpy(c->updated_at, value, sizeof(c->updated_at));
    }

    return c;
}