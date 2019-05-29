#ifndef STRUCT_H
#define STRUCT_H

// Перечисление типов строк

typedef enum {
  NONE = 0,
  FUNCTION = 1,     // Строка относится к функции
  NON_FUNCTION = 2, // Строка не относится к функции
  VAR_GLOBAL = 3, // Переменная является глобальной
  VAR_NON_GLOBAL = 4 // Переменная не является глобальной
} type;

// Хранит тип строки

typedef struct {
  unsigned int string_number; // Номер строки
  char *text;                 // Строка
  type types[2];              // Тип строки
} sString;

// Хранит информацию о переменной

typedef struct {
  char *variable_name;        // Имя переменной
  char *variable_value;       // Значение
  unsigned int string_number; // Номер строки с переменной
  type types;                 // Тип переменной
  int capacity;
} sVariable;

// Хранит информацию о функции

typedef struct {
  char *function_name; // Имя функции
  unsigned int str_number; // Номер строки, где была объявлена функция
  unsigned int open_bracket_string_number; // Строка с открывающей скобкой
  unsigned int close_bracket_string_number; // Строка с закрывающей скобкой
} sFunction;

// Структуры для хранения массивов заданных типов

typedef struct {
  sString *string;       // Хранит информацию о строке
  unsigned int capacity; // Размер массива
} stringArray;

typedef struct {
  sFunction *array;      // Хранит информацию о функции
  unsigned int capacity; // Размер массива
} functionArray;

typedef struct {
  sVariable *array; // Хранит информацию о переменной
  unsigned int capacity; // Размер массива
} variableArray;

int isVariable(stringArray strArray, int string_number, sVariable *variable, int *array_counter);
variableArray getGlobalVariables(stringArray *strArray);
functionArray getFunctions(stringArray *strArray);
int getCallTimes(stringArray strArray, char *function_name);

#endif
