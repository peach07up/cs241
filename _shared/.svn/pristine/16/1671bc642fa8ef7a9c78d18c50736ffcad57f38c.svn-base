/* This program illustrates some of the concepts involved with using
 * signals.  The idea is for a "writer" process to be able to send
 * messages to a "reader" process, using only signals.
 *
 * The first challenge is that you can't send general-purpose
 * messages with a signal -- you can just tell another process that
 * some event happened.  We solve that problem by having one event
 * represent a 0 bit and event represent a 1 bit, and then we turn
 * the messasge into a sequence of bits to send it.  (Of course,
 * we'd never do this in practice -- it's for illustration purposes
 * only.)
 * 
 * After you compile this code, you can run it by opening two
 * terminal windows, and typing
 *
 *     ./32-signal-v1 read
 *
 * into one window, and
 *
 *     ./32-signal-v1 write
 *
 * into the other.  Each process will ask you to enter the other's
 * process ID. Then you can begin typing messages into the "write"
 * process to be delivered to the "read" process.
 *
 * Try this out.  What happens?
 *
 * 1.  You generally have to type multiple characters in the writer
 *     for one character to appear in the reader.
 * 2.  Also, the reader receives garbage.
 *
 * These two problems illustrate two signaling concepts:
 *
 * a.  The kernel does not count how many of each type of signal
 *     has been received.  It only stores a bit representing whether
 *     the signal has been received since the process last handled it.
 *     Thus, if multiple SIGUSR1 signals are received before the read
 *     process handles them, all except the first are effectively lost.
 *
 * b.  The kernel doesn't guarantee that signals are delivered in
 *     the same order they are sent.
 *
 * Problem 1 is caused by (a).  Problem 2 is caused by (a) and (b).
 * 
 * Think about how you might fix these problems.  Then check
 * signal-v2 for a solution.
 *
 * NOTE: Like the code in lecture, this code omits error checks when
 * calling the various library and system calls.  Your MP code should
 * check for errors.  We omit it here so that the main steps of the
 * code are more clearly illustrated.
 */

#include <stdio.h> 
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>


/* Function declarations.  These functions actually do
 * nearly all the work. */
int  recv_bit();
char recv_char();

void send_bit(pid_t friend, int bit);
void send_char(pid_t friend, char c);

int main(int argc, char** argv) {
    pid_t    friend;
    sigset_t signals_to_mask;

    printf("I'm process %d.  Who should I talk to? ", getpid());
    scanf("%d", &friend);

    /* Reader */
    if (!strcmp(argv[1], "read")) {
        /* Block all signals */
        sigfillset(&signals_to_mask);
        sigprocmask(SIG_SETMASK, &signals_to_mask, NULL);
        /* Receive bits */
        while (1) {
            putchar(recv_char());
            fflush(stdout);
        }
    }        

    /* Writer */
    else
        while (1)
            /* Get a character from stdin and send it to my friend */
            send_char(friend, getchar());
}

int recv_bit() {
    int sig;

	/* The next 4 lines construct the set of signals that we want to
	 * wait for.  It's unfortunate that it takes 4 lines of code
	 * just to say "SIGUSR1 OR SIGUSR2"! */
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);

    /* Wait for either of those two signals */
    sigwait(&set, &sig);

    /* Interpret SIGUSR2 as a 1, and SIGUSR1 as a 0 */
    return (sig == SIGUSR2) ? 1 : 0;
}

char recv_char() {
    int i;
    char c = 0;
    for (i = 0; i < 8; i++)
        c |= recv_bit() << i;
    return c;
}

/* Sends 1 to friend if bit is nonzero; else sends 0 */
void send_bit(pid_t friend, int bit) {
    /* Send the signal that represents the corresponding bit. */
    int signal = bit ? SIGUSR2 : SIGUSR1;
    kill(friend, signal);    
}

void send_char(pid_t friend, char c) {
    int i;

    /* We're assuming that a character takes 1 byte.
     * Make sure that's true, or else die. */
    assert(sizeof(char) == 1);

    for (i = 0; i < 8; i++)
        send_bit(friend, c & (1 << i));
}

