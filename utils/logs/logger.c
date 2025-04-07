//
// Created by astrid on 2025-04-07.
//

// this line is used to disable the deprecation warnings for the use of fopen
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "logger.h"

void log_message(const char *format, ...) {
  FILE *log_file = fopen("app.log", "a");

  if (!log_file) {
    fprintf(stderr, "Unable to open log file !\n");
    return;
  }

  // Message horodating
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] ",
          t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
          t->tm_hour, t->tm_min, t->tm_sec);

  // Message formating
  va_list args;
  va_start(args, format);
  vfprintf(log_file, format, args);
  va_end(args);

  fprintf(log_file, "\n");
  fclose(log_file);
}
