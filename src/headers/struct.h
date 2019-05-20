#ifndef STRUCT_H
#define STRUCT_H

typedef enum { NONE = 0, FUNCTION = 1, NON_FUNCTION = 2 } type;

// Хранит тип строки

typedef struct {
  unsigned int string_number; // Номер строки
  char *text;                 // Строка
  type type[2];
} sString;

// Хранит информацию о функции

typedef struct {
  char *function_name; // Имя функции
  unsigned int str_num;
  unsigned int open_bracket_string_number; // Номер строки открывающей скобки
  unsigned int close_bracket_string_number; // Номер строки закрывающей скобки
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

functionArray getFunctions(stringArray *strArray);
int getCallTimes(stringArray strArray, char *function_name);

#endif
