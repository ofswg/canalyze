#ifndef STRUCT_H
#define STRUCT_H

typedef enum { NONE = 0, FUNCTION = 1, NON_FUNCTION = 2 } type;

typedef struct {
  unsigned int string_number; // Номер строки
  char *text;                 // Строка
  type type[2];
} sString;

typedef struct {
  sString *string;       // Строковый массив
  unsigned int capacity; // Размер массива
} stringArray;

#endif
