#include "headers/struct.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *isFunction(stringArray strArray, int string_number) {
  // gg
  return nameF;
}

functionArray getFunctions(stringArray *strArray) {
  functionArray result;

  for (size_t i = 0; i < strArray->capacity; i++) {
    char *nameFunction;
    if ((nameFunction = isFunction(*strArray, (int)i)) != NULL) {
      printf("%s\n", nameFunction);
      if (strchr(strArray->string[i].text, '{') != NULL) {
        // printf("%s\n", strArray->string[i].text);
      } else if (strchr(strArray->string[i + 1].text, '{') != NULL) {
        // printf("%s\n", strArray->string[i + 1].text);
      } else {
        continue;
      }
    }
  }

  return result;
}
