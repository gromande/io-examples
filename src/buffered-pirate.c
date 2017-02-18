#include <stdio.h>

typedef struct Pirate {
  char *name;
  int age;
} Pirate;

int main(int argc, char *argv[]) {
  FILE *in, *out;
  Pirate *pirate1 = malloc(sizeof(Pirate));
  pirate1->name = "Willie Nelson";
  pirate1->age = 58;

  printf("Pirate1. Name=%s; Age=%d\n", pirate1->name, pirate1->age);

  out = fopen("../data/pirate.out", "w");
  if (!out) {
    perror("fopen error");
    return -1;
  }

  if (!fwrite(&pirate1, sizeof(Pirate), 1, out)) {
    perror("fwrite errot");
    return -1;
  }

  if (fclose(out)) {
    perror("fclose error");
    return -1;
  }

printf("Pirate1. Name=%s; Age=%d\n", pirate1->name, pirate1->age);

  in = fopen("../data/pirate.out", "r");
  if (!in) {
    perror("fopen error");
    return -1;
  }

  Pirate *pirate2 = malloc(sizeof(Pirate));
  if (!fread(&pirate2, sizeof(Pirate), 1, in)) {
    perror("fread errot");
    return -1;
  }

  printf("Pirate2. Name=%s; Age=%d\n", pirate2->name, pirate2->age);

  if (fclose(in)) {
    perror("fclose error");
    return -1;
  }


  // /free(pirate1);
  free(pirate2);
  return 0;
}
