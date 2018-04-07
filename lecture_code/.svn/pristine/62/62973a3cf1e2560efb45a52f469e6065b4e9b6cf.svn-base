#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

int main(int argc, char**argv) {
	sigset_t mask;
	sigset_t orig_mask;
	sigemptyset (&mask);
	sigaddset (&mask, SIGTERM);
 
	sigprocmask(SIG_BLOCK, &mask, &orig_mask);
	
	raise(SIGTERM);

	pid_t pid = fork();

	printf("%d lowering shields....\n", (int) getpid() );
	sigprocmask(SIG_SETMASK, &orig_mask, NULL);

        if(pid==0) printf("I'm the child (%d) and I'm still alive!\n",(int)getpid());
        else printf("I'm the parent (%d) and I'm still alive!\n", (int)getpid());

	return 1;
}
