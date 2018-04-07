#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream){
  assert(lineptr);
  assert(n);
  assert(stream);
  if( ! *lineptr )  { *n = 256; *lineptr = malloc(*n);}
  size_t bytesread = 0;
  char c = 0; // Hint an int would be better (man fgetc)
  while( ferror(stream)==0 && feof(stream)==0 ){
      if (bytesread == *n) { puts("TODO extend buffer"); exit(0); }
      c = fgetc(stream);
      (*lineptr)[bytesread++] = c; 
      if(c=='\n') { (*lineptr)[bytesread++]=0; /*TODO FIX BUFFER OVERFLOW */ return bytesread; }
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
