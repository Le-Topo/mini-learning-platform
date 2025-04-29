//
// Created by astri on 2025-04-29.
//

#include "./course-part.h"

QueryResponseStatus get_course_parts_by_course_id(long course_id, CoursePartList **course_parts_list_ptr) {
    MYSQL *conn = get_mysql_connection();

    char whereClause[80];
    snprintf(whereClause, sizeof(whereClause), "WHERE course_id = %ld", course_id);

    CoursePart course_part;
    memset(&course_part, 0, sizeof(CoursePart));

    QueryResponseStatus status = select_from_table(
        conn,
        COURSE_PARTS_TABLE,
        "*",
        whereClause,
        add_fetched_course_part_to_list,
        (void **)course_parts_list_ptr
    );

    return status;
}

void add_fetched_course_part_to_list(MYSQL_ROW courseRow, MYSQL_FIELD *fields, int num_fields, void **course_parts_list_ptr) {
    CoursePart *course_part = convert_mysql_fetched_row_to_course_part(courseRow, fields, num_fields);
    course_part->next = NULL;
    course_part->prev = NULL;

    CoursePartList **list_ptr = (CoursePartList **)course_parts_list_ptr;

    if (*list_ptr == NULL) {
        *list_ptr = calloc(1, sizeof(CoursePartList));
    }

    CoursePartList *list = *list_ptr;

    if (list->head == NULL) {
        list->head = course_part;
        list->count = 1;
    } else {
        CoursePart *p = list->head;

        while (p->next) p = p->next;

        course_part->prev = p;
        p->next = course_part;
        list->count++;
    }

    log_message("Added course part: %s %d", course_part->title, list->count);
}

CoursePart* convert_mysql_fetched_row_to_course_part(MYSQL_ROW row, MYSQL_FIELD *fields, int num_fields) {
    CoursePart *course_part = calloc(1, sizeof(CoursePart));
    if (course_part == NULL) {
        log_message("Failed to allocate memory for CoursePart");
        return NULL;
    }

    for (int i = 0; i < num_fields; i++) {
        const char *name = fields[i].name;
        const char *value = row[i];

        if (strcmp(name, "id") == 0) {
            course_part->id = atol(value);
        } else if (strcmp(name, "course_id") == 0) {
            course_part->course_id = atol(value);
        } else if (strcmp(name, "title") == 0) {
            strncpy(course_part->title, value, sizeof(course_part->title));
        } else if (strcmp(name, "is_quiz") == 0) {
            course_part->is_quiz = atoi(value);
        } else if (strcmp(name, "content") == 0 && value != NULL) {
            strncpy(course_part->content, value, sizeof(course_part->content));
        } else if (strcmp(name, "order") == 0) {
            course_part->order = atoi(value);
        } else if (strcmp(name, "score_percentage") == 0) {
            course_part->score_percentage = atoi(value);
        } else if (strcmp(name, "created_at") == 0) {
            strncpy(course_part->created_at, value, sizeof(course_part->created_at));
        } else if (strcmp(name, "updated_at") == 0) {
            strncpy(course_part->updated_at, value, sizeof(course_part->updated_at));
        }
    }

    return course_part;
}