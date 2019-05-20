#include "headers/process.h"
#include "headers/struct.h"
#include "stdio.h"

int canalyse(stringArray *strArray) {

  functionArray funcArray = getFunctions(strArray);
  if (funcArray.capacity == 0) {
    printf("There are no functions in this file.\n");
    return 0;
  }

  printf("Function:\t\tCall times:\n\n");
  for (size_t i = 0; i < funcArray.capacity; i++) {
    printf("%s\t\t\t%d\n", funcArray.array[i].function_name,
           getCallTimes(*strArray, funcArray.array[i].function_name) - 1);
  }
  printf("\n");

  return 0;
}
