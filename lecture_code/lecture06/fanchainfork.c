#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void chain(int N) {
	int remain = N;
	while(--remain) {
		pid_t result = fork();
		if(result ==0) printf("I am the new child %d and my parent is %d\n", getpid(), getppid());
		
		
	}
}
void fan(int N) {
	int remain = N;
	while(--remain) {
		pid_t result = fork();
		if(result ==0) printf("I am the new child %d and my parent is %d\n", getpid(), getppid());
		
		
	}
}
int main(int argc, char**argv) {
	printf("I am %d, the first process\n", getpid() ); 
	int N = 4;
	
	if(argv[1] && !strcmp("chain", argv[1]) ) chain( N );
	else if(argv[1] && !strcmp("fan", argv[1]) ) fan( N );
	else fprintf(stderr, "Usage: %s chain|fan\n", argv[0]);
	
	sleep(1);
	return 0;
}