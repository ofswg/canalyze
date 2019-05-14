#include "headers/process.h"
#include "headers/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int canalyse(stringArray *strArray, char *inputFunction) {
  printf("\nResult:\n");
  for (size_t i = 0; i < strArray->capacity; i++) {
    if (strstr(strArray->string[i].text, inputFunction) != NULL) {
      printf("%d: %s\n", (int)i, strArray->string[i].text);
    } else {
      continue;
    }
  }
  return 0;
}
