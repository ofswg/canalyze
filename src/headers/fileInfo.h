#ifndef FILEINFO_H
#define FILEINFO_H

#include "struct.h"
#include <stdio.h>
#include <string.h>

size_t fileGetContents(FILE *fp, sString *string);
size_t fileGetString(FILE *fp);
size_t removeSpacesAtBegin(char *string);
int stok(char *str, char delim, char **pointer);

#endif
