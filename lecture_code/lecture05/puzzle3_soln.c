#include <stdio.h>
#include <unistd.h>
int main(int argc, char** argv) {
   char* lineptr;
   size_t size;
   ssize_t bytes  = getline(&lineptr, &size, stdin);
   lineptr[bytes-1] = 0;
   puts(lineptr);
   execlp(lineptr, lineptr, (char*) NULL);
   perror("FAILED!");
   return 0;
}
