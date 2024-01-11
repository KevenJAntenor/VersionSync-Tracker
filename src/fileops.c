#include "fileops.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "inf3173/config.h"
#include "utils.h"

/*
 * Voir les instructions dans le fichier README
 *
 * Astuce: vous pouvez utiliser les fonctions
 * dans le fichier utils.h
 */

const int magic = 0x1001CAFE;
struct hdr {
  int m;
  unsigned long v;
  struct timespec t;
} __attribute__((packed));


int bumpvers_fonction(const char* fname) {

  // TODO
 
  FILE* fiche;
  int magic_lue;
  unsigned long num_version = 0;
  struct timespec ts;

  struct stat   buffer;
  int open_stat = stat (fname, &buffer);

  char *flag = open_stat == 0 ? "rb+" : "wb+";

  //Ouvrire le fichier
  fiche = fopen(fname,flag);

  if (fiche == NULL) {
    perror("Erreur ouverture fichier");
    exit(EXIT_FAILURE);
  } 

  if (open_stat == 0) {
    //lire mot magic
    fread(&magic_lue, sizeof(int), 1, fiche);

    if(magic !=magic_lue){
      exit(EXIT_FAILURE);
    } 

  //Lire numero version
    fread(&num_version, sizeof(unsigned long), 1, fiche);
    num_version++;

    rewind(fiche);
    //go back to the begin of the file
  }
   
  //if(clock_gettime(CLOCK_REALTIME,&ts)==-1){
  if(clock_gettime(CLOCK_MONOTONIC,&ts)==-1){
    
    perror("clock_gettime");
    exit(EXIT_FAILURE);
  }
//Ecrire le temps dans le fichier
  fwrite(&magic, sizeof(int), 1, fiche);
  fwrite(&num_version, sizeof(unsigned long), 1, fiche);
  fwrite(&ts, sizeof(struct timespec), 1, fiche);

  fclose(fiche);

  return 0;
}



int bumpvers_commande(const char* fname) {
  
  // TODO
  pid_t pid = fork();
  if(pid ==-1){
    perror("processus fils erreur");
    exit(EXIT_FAILURE);

  } else if(pid ==0){
    //execlp("./bumpvers", "./bumpvers", fname, NULL);
    char cwd [1024];
    getcwd(cwd, sizeof(cwd));
    dirname(cwd);
    strcat(cwd, "/bin/bumpvers");

    char *arg_l [] = {"bumpvers", fname, NULL};
    execvp(cwd,arg_l );
    //exec remplacer tous dans le memory, donc, il connais . -- le repertoir courant.
    perror("Erreur avec exec de .bumpvers");

    exit(EXIT_FAILURE);
  } else {
    wait(NULL);
  }

  return 0;
}

int do_benchmark(const char* fname, fileop_t fn, int repeat, double* avg) {
  // TODO

  struct timespec debut, fin;
  double temps_total = 0;

  for (int i = 0; i < repeat; i++)
  {
    clock_gettime(CLOCK_MONOTONIC, &debut);
    fn(fname);
    clock_gettime(CLOCK_MONOTONIC, &fin);

    double temps_ecoule = (fin.tv_sec - debut.tv_sec) + (fin.tv_nsec - debut.tv_nsec)/1e9;
    //delta_time(&fin, &debut);
    //temps_total = timespec_to_second(&fin);

    temps_total+=temps_ecoule;

  }

  *avg = temps_total/repeat;
  
  return 0;
}
