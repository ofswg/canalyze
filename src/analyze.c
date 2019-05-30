#include "headers/fileInfo.h"
#include "headers/struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *isFunction(stringArray strArray, int string_number, int length, int *close_bracket) {
  char *nameF = NULL;
  int open_parameter_bracket, space_in_remaining_line;

  // Получаем расположение скобки в строке
  for (size_t i = 0; i < length; i++) {
    if (strArray.string[string_number].text[i] == '(') {
      open_parameter_bracket = i;
    }
  }

  if (strArray.string[string_number].text[length - 1] == '{') {
    *close_bracket = 1;
  } else if (strArray.string[string_number + 1].text[0] == '{') {
    *close_bracket = 0;
  }

  // "int main() {" -> "int main"
  for (size_t i = open_parameter_bracket; i < length; i++) {
    strArray.string[string_number].text[i] = '\0';
  }

  for (size_t i = 0; i < open_parameter_bracket; i++) {
    // Если последний символ Пробел
    if (strArray.string[string_number].text[open_parameter_bracket - 1] == ' ') {
      return NULL;
    }
    // Узнаем, где стоит пробел
    if (strArray.string[string_number].text[i] == ' ') {
      space_in_remaining_line = i;
    }
  }

  // Проверка на наличие пробела
  if (strchr(strArray.string[string_number].text, ' ') != NULL) {
    for (size_t i = 0; i < space_in_remaining_line + 1; i++) {
      for (size_t j = 0; j < open_parameter_bracket; j++) {
        if (strArray.string[string_number].text[j] == '=') {
          return NULL;
        }
        strArray.string[string_number].text[j] = strArray.string[string_number].text[j + 1];
      }
    }

    if (strArray.string[string_number].text[0] == '(') {
      return NULL;
    }

    nameF = (char *)calloc((size_t)strlen(strArray.string[string_number].text), sizeof(char));
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
    // Если в строке есть ( и в конце строки стоит { или в начале следующей строки стоит {
    if (strchr(strArray->string[i].text, '(') != NULL &&
        (strArray->string[i].text[length - 1] == '{' ||
         strArray->string[i + 1].text[0] == '{')) {
      int close_bracket = 0;
      // Если в строке есть функция - вернет название функции, иначе NULL
      if ((nameFunction = isFunction(*strArray, (int)i, (int)length, &close_bracket)) != NULL) {
        // Если функция возвращает указатель на какой-то тип данных
        if (nameFunction[0] == '*') {
          nameFunction[0] = ' ';
          removeSpacesAtBegin(nameFunction);
        }

        result.array[resulted_array_counter].function_name =
            calloc((size_t)strlen(nameFunction), sizeof(char));
        strcpy(result.array[resulted_array_counter].function_name,
               nameFunction);
        size_t k = 0, step = i;
        unsigned int open_bracket_count = close_bracket,
                     close_bracket_count = 0, last_bracket = 0;

        // Подсчет открывающий и закрывающих скобок
        while (k == 0) {
          if (strstr(strArray->string[step].text, nameFunction) != NULL) {
            result.array[resulted_array_counter].open_bracket_string_number = (int)step;
            result.array[resulted_array_counter].str_number = (int)step;
          }
          if (strstr(strArray->string[step].text, nameFunction) != NULL &&
              strchr(&strArray->string[step + 1].text[0], '{') != NULL) {
            result.array[resulted_array_counter].open_bracket_string_number = (int)step + 1;
            result.array[resulted_array_counter].str_number = (int)step;
          }

          if (strchr(strArray->string[step].text, '{') != NULL) {
            open_bracket_count++;
          } else if (strchr(strArray->string[step].text, '}') != NULL) {
            close_bracket_count++;
            last_bracket = (int)step;
          } else if (open_bracket_count == close_bracket_count) {
            k = 1;
          }
          step++;
          if (step == strArray->capacity) {
            k = 1;
          }
        }

        result.array[resulted_array_counter].close_bracket_string_number = last_bracket;
        for (int k = result.array[resulted_array_counter].open_bracket_string_number;
             k <= result.array[resulted_array_counter].close_bracket_string_number;
             k++) {
          strArray->string[k].types[0] = FUNCTION;
        }
        resulted_array_counter++; // Счетчик кол-ва функций
      }
    }
  }

  result.capacity = (unsigned int)resulted_array_counter;

  return result;
}

int isVariable(stringArray strArray, int string_number, sVariable *variable, int *array_counter) {
  // Избавляемся от строк с подключением библиотек и пустых строк
  if (strArray.string[string_number].text[0] == '#' || strArray.string[string_number].text[0] == '\0'
      || strchr(strArray.string[string_number].text, '(') != NULL) {
    return 0;
  }

  char *nameF = (char *)calloc((size_t)strlen(strArray.string[string_number].text), sizeof(char));
  char *pointer[20];
  int length_pointer, space_in_remaining_line;
  unsigned int length;
  int resulted_array_counter = 0;
  resulted_array_counter = *array_counter;

  if (strchr(strArray.string[string_number].text, ';') != NULL) {
    length_pointer = stok(strArray.string[string_number].text, ',', pointer);
    for (size_t i = 0; i < length_pointer; i++) {
      length = strlen(pointer[i]);
      pointer[i] = pointer[i] + 1;
      if (strchr(pointer[i], '=') != NULL) {
        for (size_t step = 0; step < length; step++) {
          if (pointer[i][step] == ' ') {
            for (size_t f = step; f < length; f++) {
              pointer[i][f] = pointer[i][f + 1];
            }
          }
        }
        char *variableString[20];
        int length_variable;

        length_variable = stok(pointer[i], '=', variableString);
        nameF = variableString[0];
        variable[resulted_array_counter].variable_value = variableString[1];
      } else {
        if (strchr(pointer[i], ';') != NULL) {
          unsigned int count = 0;
          for (size_t j = 0; j < length; j++) {
            if (pointer[i][j] == ';') {
              count++;
            }
            if (count == 1) {
              pointer[i][j] = '\0';
            }
          }
        }
        if (strchr(pointer[i], ' ') != NULL) {
          for (size_t j = 0; j < length; j++) {
            if (pointer[i][j] == ' ') {
              space_in_remaining_line = (int)j;
            }
          }
        } else if (strchr(pointer[i], '[') != NULL) {
          unsigned int count = 0;
          for (size_t j = 0; j < length; j++) {
            if (pointer[i][j] == '[') {
              count++;
            }
            if (count == 1) {
              pointer[i][j] = '\0';
            }
          }
        }
        if (space_in_remaining_line != 0) {
          for (size_t k = 0; k < space_in_remaining_line + 1; k++) {
            for (size_t j = 0; j < length - 1; j++) {
              pointer[i][j] = pointer[i][j + 1];
            }
          }
        }
        nameF = pointer[i];
      }
      variable[resulted_array_counter].variable_name = nameF;
      variable[resulted_array_counter].string_number = string_number;
      space_in_remaining_line = 0;
      resulted_array_counter++;
      // printf("[%d - %d] %s - %u\n", (int)string_number + 1, resulted_array_counter - 1, variable[resulted_array_counter - 1].variable_name, variable[resulted_array_counter - 1].types);
    }
  } else {
    return 0;
  }
  // printf("[%d]\n", resulted_array_counter);
  *array_counter = resulted_array_counter - 1;
  return 1;
}

variableArray getGlobalVariables(stringArray *strArray) {
  variableArray resultGlobalVariable;
  int array_counter = 0, index = 0;
  resultGlobalVariable.array = malloc(8 * sizeof(sVariable));

  for (size_t i = 0; i < strArray->capacity; i++) {
    if (strArray->string[i].types[0] != FUNCTION) {
      if (isVariable(*strArray, i, &resultGlobalVariable.array[index], &array_counter) == 1) {
        strArray->string[i].types[1] = VAR_GLOBAL;
        index++;
      }
    }
  }

  resultGlobalVariable.capacity = array_counter + index;
  return resultGlobalVariable;
}

variableArray getNonGlobalVariables(stringArray *strArray, functionArray funcArray) {
  variableArray resultNonGlobalVariable;
  int index = 0, array_counter = 0, index_array = 0;
  resultNonGlobalVariable.array = malloc(8 * sizeof(sVariable));

  for (size_t i = 0; i < funcArray.capacity; i++) {
    for (size_t j = funcArray.array[i].open_bracket_string_number;
                j < funcArray.array[i].close_bracket_string_number;
                j++) {
      if (strchr(strArray->string[j].text, ' ') != NULL &&
          strstr(strArray->string[j].text, "return") == NULL) {
        if (isVariable(*strArray, j, &resultNonGlobalVariable.array[index], &array_counter) == 1) {
          strArray->string[j].types[1] = VAR_NON_GLOBAL;
          index_array += array_counter;

          index++;
        }
      }
    }
  }

  resultNonGlobalVariable.capacity = array_counter + index;
  return resultNonGlobalVariable;
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
