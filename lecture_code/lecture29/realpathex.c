#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  while(1) {
    puts("\nEnter a path");
    char buf[200];
    char*ok = fgets(buf, sizeof(buf), stdin);
    if(!ok || strlen(ok) ==0) break;

    // assumes last char is a newline
    buf[ strlen(buf)-1] = 0; 

    char*result = realpath(buf,NULL);

    if(!result) { puts("Not a valid path"); continue; }

    puts(result);
    free(result);
  }
  return 42;
}
