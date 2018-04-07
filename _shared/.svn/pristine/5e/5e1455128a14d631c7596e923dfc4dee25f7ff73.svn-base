#include <stdio.h>
#include <unistd.h>
int main(int argc, char**argv) {
   printf("Executing %s ...\n", argv+1);
   execvp( argv + 1, argv + 1);
   perror("Failed to be all powerful");
   return 0;
}
