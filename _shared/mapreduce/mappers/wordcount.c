/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mapper.h"

void replace_chars(char *str) {
  while (*str) {
    if (*str == ':')
      *str = ';';
    // prevent newline from messing up with strtok()
    if (*str == '\n')
      *str = ' ';
    str++;
  }
}

void mapper(const char *data, FILE *output) {
  char *data_copy = strdup(data);
  if (data_copy)
    replace_chars(data_copy);
  char *datum = strtok(data_copy, " ");
  while (datum) {
    // the difference is just a few pixels :-)
    fprintf(output, "%s: 1\n", datum);
    datum = strtok(NULL, " ");
  }

  free(data_copy);
}

MAKE_MAPPER_MAIN(mapper)
