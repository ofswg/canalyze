#include "headers/fileInfo.h"
#include <stdlib.h>

size_t fileGetString(FILE *fp) {
  fpos_t fpos;
  fgetpos(fp, &fpos);
  char *buf = NULL;
  size_t len;
  size_t size = 0;
  while (getline(&buf, &len, fp) != -1) {
    size++;
  }
  free(buf);
  fsetpos(fp, &fpos);
  return size;
}
