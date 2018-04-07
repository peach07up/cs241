/* 
 * Readers-writers solution with condition variables.
 * Weak reader priority: writers may starve.
 * Brighten Godfrey <pbg@illinois.edu>
 *
 * Note: program is not a complete example -- we didn't actually start any threads.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/* Global variables */
pthread_mutex_t m;
pthread_cond_t  turn; /* Event: it's our turn */
int writing;
int reading;
 
void init(void) {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&turn, NULL);
    reading = 0;
    writing = 0;
}

void reader(void) 
{
    pthread_mutex_lock(&m);
    while (writing)
        pthread_cond_wait(&turn, &m);
    reading++;
    pthread_mutex_unlock(&m);

    /* Reading would happen here */

    pthread_mutex_lock(&m);
    reading--;
    pthread_cond_signal(&turn);
    pthread_mutex_unlock(&m);
}

void writer(void) 
{
    pthread_mutex_lock(&m);
    while (reading || writing)
        pthread_cond_wait(&turn, &m);
    writing++;
    pthread_mutex_unlock(&m);

    /* Writing would happen here */

    pthread_mutex_lock(&m);
    writing--;
    pthread_cond_signal(&turn);
    pthread_mutex_unlock(&m);
}

int main(void) {
    init();
}