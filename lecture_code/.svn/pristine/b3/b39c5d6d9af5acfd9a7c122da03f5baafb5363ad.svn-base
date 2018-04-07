#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void quit(char*mesg) {perror(mesg); exit(1);}

void handler(int sig) {
	char*mesg = "SIGTERM CAUGHT!\n";
	write(1,mesg, strlen(mesg));
}

int main() {
//	signal( SIGTERM, handler);

	puts("  prog2");
        sigset_t pending;
        if( sigpending( &pending) <0) quit("sigpending");

        printf("SIGTERM sigismember:%d\n", sigismember(&pending, SIGTERM));

	sleep(2);
	sigset_t mask;
	sigemptyset(&mask);

	puts("Changing mask - lowering shields!!");
	sigprocmask(SIG_SETMASK, &mask, NULL);

	puts("Shields are down");
	return 0;
}
