#include "headers/fileInfo.h"
#include "headers/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *isFunction(stringArray strArray, int string_number, int length) {
  char *nameF = NULL;
  int open_parameter_bracket, space_in_remaining_line;

  for (size_t i = 0; i < length; i++) { // Получаем расположение скобки в строке
    if (strArray.string[string_number].text[i] == '(') {
      open_parameter_bracket = i;
    }
  }

  for (size_t i = open_parameter_bracket; i < length; i++) {
    strArray.string[string_number].text[i] =
        '\0'; // "int main() {" -> "int main"
  }

  for (size_t i = 0; i < open_parameter_bracket; i++) {
    if (strArray.string[string_number].text[open_parameter_bracket - 1] ==
        ' ') { // Если последний символ Пробел
      strArray.string[string_number].text[open_parameter_bracket - 1] = '\0';
    }
    if (strArray.string[string_number].text[i] ==
        ' ') { // Узнаем, где стоит пробел
      space_in_remaining_line = i;
    }
  }

  if (strchr(strArray.string[string_number].text, ' ') !=
      NULL) { // Проверка на наличие пробела
    for (size_t i = 0; i < space_in_remaining_line + 1; i++) {
      for (size_t j = 0; j < open_parameter_bracket; j++) {
        strArray.string[string_number].text[j] = // "int main" -> "main"
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
  for (size_t i = 0; i < strArray->capacity - 1; i++) {
    char *nameFunction;
    length = strlen(strArray->string[i].text);
    if (strArray->string[i].text[length - 1] == '{' ||
        strArray->string[i + 1].text[0] == '{') {
      // Если в конце строки стоит { или в начале следующей строки стоит {
      if ((nameFunction = isFunction(*strArray, (int)i, (int)length)) != NULL) {
        // Если в строке есть функция - вернет название функции, иначе NULL

        if (nameFunction[0] == '*') {
          // Если функция возвращает указатель на какой-то тип данных
          nameFunction[0] = ' ';
          removeSpacesAtBegin(nameFunction);
        }

        result.array[resulted_array_counter].function_name =
            calloc((size_t)strlen(nameFunction), sizeof(char));
        strcpy(result.array[resulted_array_counter].function_name,
               nameFunction);

        resulted_array_counter++; // Счетчик кол-ва функций
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
