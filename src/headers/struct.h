#ifndef STRUCT_H
#define STRUCT_H

// Перечисление типов строк

typedef enum {
  NONE = 0,
  FUNCTION = 1,
  NON_FUNCTION = 2,
  VAR_GLOBAL = 3,
  VAR_NON_GLOBAL = 4
} type;

// Хранит тип строки

typedef struct {
  unsigned int string_number; // Номер строки
  char *text;                 // Строка
  type types[2];              // Тип строки
} sString;

/* Хранит информацию о переменной

typedef struct {
  char *variable_name;        // Имя переменной
  char *variable_value;       // Значение
  unsigned int string_number; // Номер строки с переменной
  type types;                 // Тип переменной
} sVariable; */

// Хранит информацию о функции

typedef struct {
  char *function_name; // Имя функции
} sFunction;

// Структуры для хранения массивов заданных типов

typedef struct {
  sString *string;       // Строковый массив
  unsigned int capacity; // Размер массива
} stringArray;

typedef struct {
  sFunction *array;
  unsigned int capacity;
} functionArray;

/* typedef struct {
  sVariable *array;
  unsigned int capacity;
} variableArray; */

functionArray getFunctions(stringArray *strArray);
int getCallTimes(stringArray strArray, char *function_name);

#endif
