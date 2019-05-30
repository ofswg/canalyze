#ifndef PROCESS_H
#define PROCESS_H

#include "struct.h"

int canalyse(stringArray *strArray);
int findVariableConflicts(stringArray strArray, variableArray global, variableArray non_global, functionArray funcArray);
void printfFunctions(stringArray strArray, functionArray funcArray);

#endif
