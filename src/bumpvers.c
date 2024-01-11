#include <stdio.h>
#include <stdlib.h>

#include "fileops.h"
#include "utils.h"

int main(int argc, char** argv) {
  // Faire un appel a la fonction fileops_syscall() de la librairie.
  // Utiliser le nom de fichier passe en argument

  if (argc < 2) {
    printf("missing argument\n");
    return EXIT_FAILURE;
  }

  int ret = bumpvers_fonction(argv[1]);

  if (ret < 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
