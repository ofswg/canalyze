#include "headers/fileInfo.h"
#include "headers/process.h"
#include "headers/struct.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  if (argc == 1 || argc > 2) {
    printf("Usage: /canalyze 'file.c'\n");
    return 0;
  }
  const char *file = argv[1];
  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    printf("Can't open file for read\n");
    return -1;
  }

  stringArray strArray;
  strArray.capacity = (unsigned int)fileGetString(fp);
  strArray.string = calloc(strArray.capacity, sizeof(sString));
  fileGetContents(fp, strArray.string);

  canalyse(&strArray);
  fclose(fp);
  free(strArray.string);
  return 0;
}
