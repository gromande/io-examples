#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct Pirate {
  char *name;
  int age;
} Pirate;

int main(int argc, char *argv[]) {
  int in, out;

  Pirate *pirate1 = malloc(sizeof(Pirate));
  pirate1->name = "Willie Nelson";
  pirate1->age = 58;

  printf("Pirate1. Name=%s; Age=%d\n", pirate1->name, pirate1->age);

  out = creat("../data/pirate.out", 0644);
  if (out == -1) {
    perror("creat error");
    return -1;
  }

  size_t count = sizeof(Pirate);
  ssize_t nr;

  nr = write(out, pirate1, count);
  if (nr == -1) {
    perror("write error");
    return -1;
  } else if (nr != count) {
    printf("Error writing\n");
    return -1;
  }

  if (close(out) == -1) {
    perror("close error");
    return -1;
  }

  in = open("../data/pirate.out", O_RDONLY);
  if (in == -1) {
    perror("open error");
    return -1;
  }

  Pirate *pirate2 = malloc(sizeof(Pirate));
  nr = read(in, pirate2, count);

  if (nr == -1) {
    perror("read error");
    return -1;
  } else if (nr != count) {
    printf("Error reading\n");
    return -1;
  }

  printf("Pirate2. Name=%s; Age=%d\n", pirate2->name, pirate2->age);

  if (close(in) == -1) {
    perror("close error");
    return -1;
  }

  free(pirate1);
  free(pirate2);
  return 0;
}
