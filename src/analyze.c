#include "headers/struct.h"
#include <stdio.h>

functionArray getFunctions(stringArray *strArray) {
  functionArray result;

  unsigned int last_bracket = 0;

  for (size_t i = 0; i < strArray->capacity; i++) {
    printf("%s\n", strArray->string[i].text);
  }

  return result;
}
