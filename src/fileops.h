#ifndef INF3173_TP1_FILEOPS_H
#define INF3173_TP1_FILEOPS_H

#ifdef __cplusplus
extern "C" {
#endif

extern const int magic;

typedef int (*fileop_t)(const char* fname);

int bumpvers_fonction(const char* fname);
int bumpvers_commande(const char* fname);

int do_benchmark(const char* fname, fileop_t fn, int repeat, double* avg);

#ifdef __cplusplus
}
#endif

#endif
