#include "headers/process.h"
#include "headers/colors.h"
#include "headers/struct.h"
#include "stdio.h"

int canalyse(stringArray *strArray) {

  for (int i = 0; i < strArray->capacity; i++) {
    strArray->string[i].types[0] = NON_FUNCTION;
  }

  functionArray funcArray = getFunctions(strArray);
  if (funcArray.capacity == 0) {
    printf("%sTHERE ARE NO FUNCTIONS IN THIS FILE.%s\n", red, RESET);
    return 0;
  }

  variableArray varGlobalArray = getGlobalVariables(strArray);
  variableArray varNonGlobalArray = getNonGlobalVariables(strArray, funcArray);

  printf("Var Global: %d\n", varGlobalArray.capacity);
  for (size_t i = 0; i < varGlobalArray.capacity; i++) {
    printf("[%d] %s\n", (int)i, varGlobalArray.array[i].variable_name);
  }

  printf("Var Non Global: %d\n", varNonGlobalArray.capacity);
  for (size_t i = 0; i < varNonGlobalArray.capacity; i++) {
    printf("[%d] %s\n", (int)i, varNonGlobalArray.array[i].variable_name);
  }

  printfFunctions(*strArray, funcArray);
  // findVariableConflicts(*strArray, varGlobalArray, varNonGlobalArray, funcArray);

  return 0;
}

/* int findVariableConflicts(stringArray strArray, variableArray global, variableArray non_global, functionArray funcArray) {
  for (size_t i = 0; i < global.capacity; i++) {
    for (size_t j = 0; j < non_global.capacity; j++) {

    }
  }
  return 0;
} */

void printfFunctions(stringArray strArray, functionArray funcArray) {
  printf("\n%sFUNCTION:\t\tCALL TIMES:%s\n", red, RESET);
  for (size_t i = 0; i < funcArray.capacity; i++) {
    printf("%s%s\t\t\t%d%s\n", green, funcArray.array[i].function_name,
           getCallTimes(strArray, funcArray.array[i].function_name) - 1,
           RESET);
  }
  printf("\n");
}
