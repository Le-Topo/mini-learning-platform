//
// Created by astrid on 2025-04-07.
//

#ifndef COURSE_LEARNER_H
#define COURSE_LEARNER_H

#include "utils/enums/course-learning-status.h"

// This struct represents the relationship between a learner and a course.
struct CourseLearner {
  long id;
  long course_id; // Foreign key to Course
  long learner_id; // Foreign key to User
  long current_part_id; // Foreign key to CoursePart
  int score; // Score of the learner in the course, if applicable
  CourseLearningStatus *status; // Status of the learner in the course (e.g: "in progress", "completed")
  int progress; // Progress of the learner in the course (0-100)


  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct CourseLearner CourseLearner;

#endif //COURSE_LEARNER_H
