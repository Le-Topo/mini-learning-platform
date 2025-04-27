//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_LEVEL_H
#define COURSE_LEVEL_H

enum CourseLevel {
  BEGINNER = 1,
  INTERMEDIATE = 2,
  ADVANCED = 3,
};
typedef enum CourseLevel CourseLevel;

char* get_course_level_name(CourseLevel level);

int get_course_level_color_pair(CourseLevel level);

#endif //COURSE_LEVEL_H
