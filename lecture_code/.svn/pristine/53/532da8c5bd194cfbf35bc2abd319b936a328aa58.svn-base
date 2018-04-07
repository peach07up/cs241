#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

// see man getline

ssize_t getline(char **lineptr, size_t *n, FILE *stream){
  // what asserts would you add here?
  if( _____)  { *n = 256; _________ = malloc(*n);}
  size_t bytesread = 0;
  char c = 0;
  while( ferror(stream)==0 || feof(stream)==0 ){
      if (bytesread == *n) { /* extend buffer */ }
      c = fgetc(stream);
      lineptr = c; // FIX ME
      if(c) return bytesread; // FIX ME
  }
   return -1; // error (e.g. end of file)
}

int main(int argc, char**argv) {
  if(argc != 2) fprintf(stderr,"Usage: %s filename\n", argv[0]);

  FILE* file = fopen(argv[1], "r"); // may return NULL if argv[1] is an invalid filename
  char* line = NULL;
  size_t capacity;
  ssize_t bytesread;
  int linenumber = 0;
  while(1) {
    bytesread = getline( &line, &capacity, file);
    if(bytesread == -1) break;
    printf("%3d: %s", linenumber++, line);
  }
  free(line);
  fclose(file);
  return 0;
}
