#define _GNU_SOURCE
#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "fileops.h"
#include "utils.h"

struct bench {
  char* output;
  char* method;
  int repeat;
};

void print_usage() { fprintf(stderr, "Usage: %s [-omrh]\n", "fileops"); }

int main(int argc, char** argv) {
  printf("fileops\n");
  fix_path();
  printf("bidon\n");

  struct option options[] = {{"output", 1, 0, 'o'},  //
                             {"method", 1, 0, 'm'},  //
                             {"repeat", 1, 0, 'r'},  //
                             {"help", 0, 0, 'h'},    //
                             {0, 0, 0, 0}};

  struct bench bench = {
      .output = NULL,
      .method = "fonction",
      .repeat = 1,
  };

  int opt;
  int idx;
  while ((opt = getopt_long(argc, argv, "o:m:r:h", options, &idx)) != -1) {
    switch (opt) {
      case 'o':
        bench.output = optarg;
        break;
      case 'm':
        bench.method = optarg;
        break;
      case 'r': {
        bench.repeat = atoi(optarg);
      } break;
      case 'h':
      default:
        print_usage();
    }
  }
  printf("hello\n");

  {
    // Options summary
    printf("options\n");
    printf(" output          : %s\n", bench.output);
    printf(" method          : %s\n", bench.method);
    printf(" repeat          : %d\n", bench.repeat);
  }

  if (!bench.output) {
    print_usage();
    return EXIT_FAILURE;
  }

  fileop_t fn = NULL;

  if (strcmp(bench.method, "commande") == 0) {
    fn = bumpvers_commande;
  } else if (strcmp(bench.method, "fonction") == 0) {
    fn = bumpvers_fonction;
  } else {
    printf("unkown function: %s\n", bench.method);
    return EXIT_FAILURE;
  }

  // On fait un appel à la fonction bumpvers_benchmark()
  // pour mesurer le temps d'exécution moyen
  double avg = 0.0;
  int res = do_benchmark(bench.output, fn, bench.repeat, &avg);
  printf("temps moyen: %0.3f us\n", avg * 1000000);
  if (res < 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
