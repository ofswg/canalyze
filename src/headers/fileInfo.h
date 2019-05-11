#ifndef FILEINFO_H
#define FILEINFO_H

#include "struct.h"
#include <stdio.h>

size_t fileGetContents(FILE *fp, sString *string);
size_t fileGetString(FILE *fp);

#endif
