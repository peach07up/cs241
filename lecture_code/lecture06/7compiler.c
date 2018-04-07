#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
	char * compiler = "gcc";
	int main(int argc, char** argv) {
	  if(argc != 2) {
	    fprintf(stderr,"%s prog.c",argv[0]);
	    exit(1); 
	  }
	  char* target = argv[1];
	  while(1) {
	    pid_t child = fork();

	    if(/**/){ // I'm the child 

	      execlp( );

	      perror(compiler); 
	      exit(1);
	    }
	    int status=0;
	  
	
	    if( /**/                          ) break;
	    sleep(5);
	  }
	  puts("running your program");
	  execlp("./a.out","./a.out",(const char*)NULL);
	  perror("Failed to run ./a.out");
	  return 1;
}
