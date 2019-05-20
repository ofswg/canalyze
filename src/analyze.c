#include "headers/struct.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *isFunction(stringArray strArray, int string_number, int length) {
  char *nameF = NULL;
  char *string_to_analyse = strArray.string[string_number].text;
  int open_parameter_bracket, space_in_remaining_line;
  for (size_t i = 0; i < length; i++) {
    if (strArray.string[string_number].text[i] == '(') {
      open_parameter_bracket = i;
    }
  }

  for (size_t i = open_parameter_bracket; i < length; i++) {
    strArray.string[string_number].text[i] = '\0';
  }

  for (size_t i = 0; i < open_parameter_bracket; i++) {
    if (strArray.string[string_number].text[open_parameter_bracket - 1] ==
        ' ') {
      strArray.string[string_number].text[open_parameter_bracket - 1] = '\0';
    }
    if (strArray.string[string_number].text[i] == ' ') {
      space_in_remaining_line = i;
    }
  }

  if (strchr(strArray.string[string_number].text, ' ') != NULL) {
    for (size_t i = 0; i < space_in_remaining_line + 1; i++) {
      for (size_t j = 0; j < open_parameter_bracket; j++) {
        strArray.string[string_number].text[j] =
            strArray.string[string_number].text[j + 1];
      }
    }
    nameF = (char *)calloc((size_t)strlen(strArray.string[string_number].text),
                           sizeof(char));
    nameF = strArray.string[string_number].text;
  } else {
    return NULL;
  }

  return nameF;
}

functionArray getFunctions(stringArray *strArray) {
  functionArray result;
  result.array = calloc(8, sizeof(sFunction));

  size_t length = 0, resulted_array_counter = 0;
  for (size_t i = 0; i < strArray->capacity; i++) {
    char *nameFunction;
    length = strlen(strArray->string[i].text);
    if (strArray->string[i].text[length - 1] == '{') {
      if ((nameFunction = isFunction(*strArray, (int)i, (int)length)) != NULL) {
        result.array[resulted_array_counter].function_name =
            calloc((size_t)strlen(nameFunction), sizeof(char));
        strcpy(result.array[resulted_array_counter].function_name,
               nameFunction);
        resulted_array_counter++;
      }
    }
  }
  result.capacity = (unsigned int)resulted_array_counter;
  return result;
}

int getCallTimes(stringArray strArray, char *function_name) {
  int call_times = 0;
  for (size_t j = 0; j < strArray.capacity; j++) {
    if (strstr(strArray.string[j].text, function_name) != NULL) {
      call_times++;
    }
  }
  return call_times;
}
