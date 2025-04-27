//
// Created by astri on 2025-04-26.
//

#include "./course-level.h"

char *get_course_level_name(CourseLevel level) {
    switch (level) {
        case BEGINNER:
            return "Debutant";
        case INTERMEDIATE:
            return "Intermediaire";
        case ADVANCED:
            return "Avance";
        default:
            return "Inconnu";
    }
}

int get_course_level_color_pair(CourseLevel level) {
    switch (level) {
        case BEGINNER:
            return 2; // Green
        case INTERMEDIATE:
            return 5; // Yellow
        case ADVANCED:
            return 1; // Red
        default:
            return 0; // Default color
    }
}
