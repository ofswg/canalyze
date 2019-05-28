#include "headers/process.h"
#include "headers/colors.h"
#include "headers/struct.h"
#include "stdio.h"

int canalyse(stringArray *strArray) {

  functionArray funcArray = getFunctions(strArray);
  if (funcArray.capacity == 0) {
    printf("%sTHERE ARE NO FUNCTIONS IN THIS FILE.%s\n", red, RESET);
    return 0;
  }

  printf("\n%sFUNCTION:\t\tCALL TIMES:%s\n", red, RESET);
  for (size_t i = 0; i < funcArray.capacity; i++) {
    printf("%s%s\t\t\t%d%s\n", green, funcArray.array[i].function_name,
           getCallTimes(*strArray, funcArray.array[i].function_name) - 1,
           RESET);
  }
  printf("\n");

  return 0;
}
