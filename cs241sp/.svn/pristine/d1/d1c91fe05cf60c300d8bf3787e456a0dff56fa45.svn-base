#define _GNU_SOURCE

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "camelCaser.h"
#include <stddef.h>

char **camel_caser(const char *input_str) {
    if (input_str == NULL ) return NULL;
    
    char output_str[strlen(input_str)];
    strcpy(output_str, input_str);
    
    char ** array = malloc(100);
    char * str_tok = strtok(output_str, ".");
  
    int i = 0;
    while (str_tok != NULL) {
        array[i] = strdup(str_tok);
        int j = 0;
        while (array[i][j] != '\0') {
            if ( isalpha(array[i][j]) && j == 0) array[i][j] = tolower(array[i][j]);
            if ( isalpha(array[i][j]) &&  array[i][j] == ' ' ) (array[i][j]) = toupper(array[i][j]);
            j++;
        }
        str_tok = strtok(NULL, ".");
        i++;
    }
    return array;
}