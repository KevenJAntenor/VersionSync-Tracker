#ifndef INF3173_UTILS_H_
#define INF3173_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

struct timespec;

int is_regular_file(const char* path);
int is_dir(const char* path);
int ends_with(const char* str, const char* suffix);
int fix_path();
void delta_time(struct timespec* t2, struct timespec* t1);
double timespec_to_second(struct timespec* t);

#ifdef __cplusplus
}
#endif

#endif
