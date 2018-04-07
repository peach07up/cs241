/* This commentary assumes you have read the signal-v1 code.
 * To fix the two problems of signal-v1, the intuition is to
 * have the writer only send one bit at a time.  It then
 * waits to get a receipt acknowledgement from the reader before
 * continuing to send more bits.  The basic structure of this
 * code is the same as signal-v1.  I've put in comments where
 * they differ.
 *
 * (If you would like something else fun to think about: How would
 * you go about doing this if you had only one signal (say, SIGUSR1)
 * rather than two (SIGUSR1 and SIGUSR2)?)
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

int get_next_signal();

int  recv_bit(pid_t friend);
char recv_char(pid_t friend);

void send_bit(pid_t friend, int bit);
void send_char(pid_t friend, char c);


int main(int argc, char** argv) {
    pid_t friend;

    /* This time, we need to block signals in both the reader
     * and the writer, since they'll both be using sigwait()
     * to synchronously receive signals.  I say it's "synchronous"
     * because we're explicitly waiting for a signal, rather than
     * having a signal handler be called when the signal arrives. */
    sigset_t signals_to_mask;
    sigfillset(&signals_to_mask);
    sigprocmask(SIG_SETMASK, &signals_to_mask, NULL);

    printf("I'm process %d.  Who should I talk to? ", getpid());
    scanf("%d", &friend);

    /* Reader */
    if (!strcmp(argv[1], "read")) {
        while (1) {
            putchar(recv_char(friend));
            fflush(stdout);
        }
    }        

    /* Writer */
    else
        while (1)
            send_char(friend, getchar());
}

/* Code common to both the reader and writer */
int get_next_signal() {
    int sig;
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    
    sigwait(&set, &sig);
    return sig;
}

int recv_bit(pid_t friend) {
    int bit = (get_next_signal() == SIGUSR2) ? 1 : 0;
    /* Acknowledge the message.  The fact that we send SIGUSR1
     * here isn't important -- we could have sent SIGUSR2 instead. */
    kill(friend, SIGUSR1);
    return bit;
}

char recv_char(pid_t friend) {
    int i;
    char c = 0;
    for (i = 0; i < 8; i++)
        c |= recv_bit(friend) << i;
    return c;
}

void send_bit(pid_t friend, int bit) {
    int signal = bit ? SIGUSR2 : SIGUSR1;
    kill(friend, signal);    
}

void send_char(pid_t friend, char c) {
    int i;
    assert(sizeof(char) == 1);
    for (i = 0; i < 8; i++) {
        /* Send message */
        send_bit(friend, c & (1 << i));
        /* Wait until my friend acknowledges the message */
        get_next_signal();
    }
}