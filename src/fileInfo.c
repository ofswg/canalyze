#include "headers/fileInfo.h"
#include <stdlib.h>

size_t fileGetContents(FILE *f, sString *string) {
  char *buffer = NULL;
  size_t len;
  size_t counter = 0;
  while ((getline(&buffer, &len, f)) != -1) {
    char *strbuf = malloc(len);
    removeSpacesAtBegin(buffer);
    char *pos;
    if ((pos = strchr(buffer, '\n')) != 0) {
      buffer[pos - buffer] = '\0';
    }
    strcpy(strbuf, buffer);
    string[counter].text = strbuf;
    string[counter].string_number = (unsigned int)counter;
    counter++;
  }
  return counter;
}

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

size_t removeSpacesAtBegin(char *string) {
  int i = 0;
  size_t ssize = (size_t)strlen(string);
  while (string[i] == ' ') {
    if (string[i] != ' ')
      break;
    i++;
  }
  size_t k = 0;
  for (int j = i; j < ssize + 1; j++) {
    string[k] = string[j];
    k++;
  }
  ssize -= i;
  return ssize;
}
