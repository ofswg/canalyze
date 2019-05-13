#include "headers/process.h"
#include "headers/struct.h"
#include "stdio.h"

int canalyse(stringArray *strArray) {

  functionArray funcArray = getFunctions(strArray);
  printFunctions(*strArray, funcArray);

  return 0;
}

void printFunctions(stringArray strArray, functionArray funcArray) {
  printf("Functions\t Call times\n");
  /* Code */
  printf("\n");
}
