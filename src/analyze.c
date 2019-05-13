#include "headers/struct.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *isFunction(stringArray strArray, int string_number) {
  char *nameF = malloc(sizeof(char));
  char *regptr = "^([A-Za-z0-9_]+)";

  regex_t regex;
  int regi = regcomp(&regex, regptr, REG_EXTENDED);
  if (regi) {
    return NULL;
  }
  regmatch_t regmatch[2];
  char *string_analyse = strArray.string[string_number].text;
  int status = regexec(&regex, string_analyse, 2, regmatch, 0);
  if (status) {
    return NULL;
  }
  printf("%d : %d \n", (int)regmatch[1].rm_eo, (int)regmatch[1].rm_so);

  regfree(&regex);
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
