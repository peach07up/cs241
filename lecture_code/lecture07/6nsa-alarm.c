#include <stdio.h>
#include <unistd.h>

void main(int argc, char**argv) {
   char result[20];
   puts("You have 4 seconds");
   while(1) {
      puts("Secret backdoor NSA Password?");
      char* rc = fgets( result, sizeof(result) , stdin);
      if(*result='#') break;
  }
  puts("Congratulations. Connecting to NSA ...");
  execlp("ssh", "ssh", "nsa-backdoor.net", (char*)NULL);
  perror("Do you not have ssh installed?");
}
