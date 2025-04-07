//
// Created by astrid on 2025-04-07.
//

#ifndef LEARNER_PROGRESS_H
#define LEARNER_PROGRESS_H

struct LearnerProgress {
  long id;
  long learner_id; // Foreign key to User
  long course_part_id; // Foreign key to CoursePart
  int score; // Score of the learner in the part, if applicable
  int progress; // Progress of the learner in the part (0-100)
  char *started_at; // Timestamp of when the learner started the part
  char *completed_at; // Timestamp of when the learner completed the part

  char *created_at; // ISO 8601 format
  char *updated_at; // ISO 8601 format
};
typedef struct LearnerProgress LearnerProgress;

#endif //LEARNER_PROGRESS_H
