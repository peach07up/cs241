/* NOTE: Like the code in lecture, this code omits error checks when
 * calling the various library and system calls.  Your MP code should
 * check for errors.  We omit it here so that the main steps of the
 * code are more clearly illustrated.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/* Our signal handler:  We will set it up so that this function
 * is called whenever the program receives a SIGINT (which is
 * caused by the user pressing control-c).
 */

void handler(int sig)
{
    /* This is unsafe: You should not use printf() in a signal handler,
     * because it may block (e.g. if the program was in the middle of another
     * printf() when the signal was caught).  You could use write() but
     * really you should avoid I/O in a signal handler.  Here we use printf()
     * to keep it a simple example.
     */
	printf("Caught signal!\n");
}

int main(int argc, char** argv)
{
    /* Install the signal handler for the signal SIGINT */
	signal(SIGINT, handler);

	while (1) {
        printf("Fish.\n");
        sleep(1);
	}
}
