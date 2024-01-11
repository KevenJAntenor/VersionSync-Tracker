#define _GNU_SOURCE
#include "utils.h"

#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// Source:
// https://stackoverflow.com/questions/4553012/checking-if-a-file-is-a-directory-or-just-a-file
int is_regular_file(const char* path) {
  struct stat path_stat;
  if (stat(path, &path_stat) != 0) {
    return 0;
  }
  return S_ISREG(path_stat.st_mode);
}

int is_dir(const char* path) {
  struct stat path_stat;
  if (stat(path, &path_stat) != 0) {
    return 0;
  }
  return S_ISDIR(path_stat.st_mode);
}

// Source:
// https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
int ends_with(const char* str, const char* suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  return (str_len >= suffix_len)
         && (!memcmp(str + str_len - suffix_len, suffix, suffix_len));
}

int fix_path() {
  char* path = realpath("/proc/self/exe", NULL);
  char* pos = strrchr(path, '/');
  pos[0] = '\0';
  char* cur_path = getenv("PATH");
  if (!cur_path || ends_with(cur_path, path)) {
    free(path);
    return 0;
  }

  char* new_path;
  int ret = asprintf(&new_path, "%s:%s", cur_path, path);
  if (ret < 0) {
    free(path);
    return 0;
  }

  setenv("PATH", new_path, 1);
  free(new_path);
  free(path);
  return 0;
}

/*
 * Utilitaire pour convertir struct timespec en secondes
 */
void delta_time(struct timespec* t2, struct timespec* t1) {
  t2->tv_sec = t2->tv_sec - t1->tv_sec;
  t2->tv_nsec = t2->tv_nsec - t1->tv_nsec;
  if (t2->tv_nsec < 0) {
    t2->tv_sec--;
    t2->tv_nsec += 1000000000UL;
  }
}

double timespec_to_second(struct timespec* t) {
  return t->tv_sec + t->tv_nsec / 1E9;
}
