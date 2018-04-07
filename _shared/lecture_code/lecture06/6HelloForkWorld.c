#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
char * m = "World";
 	int main() {
 	  int a = 0;
 	  pid_t f = fork();
 	  if(f == -1) { perror("fork failed!"); exit(1); }

 	  if(f==0) {/* child process */ m = "Hello";}

 	  else { // I'm the parent
 	     printf("Waiting for %ld to finish\n", (long)f);
	    waitpid( f, NULL, 0 );
 
 	  }
 	  puts(m);
 	  return 42;
 	}
