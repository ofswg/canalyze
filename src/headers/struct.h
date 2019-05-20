#ifndef STRUCT_H
#define STRUCT_H

// Хранит тип строки

typedef struct {
  unsigned int string_number; // Номер строки
  char *text;                 // Строка
} sString;

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

functionArray getFunctions(stringArray *strArray);
int getCallTimes(stringArray strArray, char *function_name);

#endif
