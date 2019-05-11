#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  if (argc == 1 || argc > 2) {
    printf("Usage: /canalyze 'file.c'\n");
    return 0;
  }
  const char *file = argv[1];
  FILE *f = fopen(file, "r");
  if (f == NULL) {
    printf("Can't open file for read\n");
    return -1;
  }

  return 0;
}
