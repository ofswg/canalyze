#include "headers/colors.h"
#include "headers/fileInfo.h"
#include "headers/process.h"
#include "headers/struct.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
  if (argc == 1 || argc > 2) {
    printf("%sUSAGE: /CANALYZE 'FILE.C'%s\n", red, RESET);
    return 0;
  }
  const char *file = argv[1];
  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    printf("%sCAN'T FILE FOR READ%s\n", red, RESET);
    return -1;
  }

  stringArray strArray;
  strArray.capacity =
      (unsigned int)fileGetString(fp); // Количество строк в файле
  strArray.string = calloc(strArray.capacity, sizeof(sString));
  fileGetContents(fp, strArray.string); // Содержимое каждой строки файла

  canalyse(&strArray);
  fclose(fp);
  free(strArray.string);
  return 0;
}
