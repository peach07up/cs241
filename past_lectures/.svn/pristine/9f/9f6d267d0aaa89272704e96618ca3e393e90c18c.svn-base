/* 
 * Producer-consumer solution with condition variables.
 * 
 * Brighten Godfrey <pbg@illinois.edu>
 *
 * Note: program is not a complete example -- we didn't actually start any threads.
 * And we don't actually have a buffer.  We just keep track of how many imaginary
 * items we have in the bufffer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/* Global variables */
pthread_mutex_t m;
pthread_cond_t  item_available; /* Event: new item inserted */
pthread_cond_t  space_available; /* Event: item removed */
int items_in_buffer;
int max_items;
 
void init(void) {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&item_available, NULL);
    pthread_cond_init(&space_available, NULL);
    items_in_buffer = 0;
    max_items = 100;
}

void producer(void) 
{
    pthread_mutex_lock(&m);
    while (items_in_buffer == max_items)
        pthread_cond_wait(&space_available, &m);
    /* Produce item */
    items_in_buffer++;
    pthread_cond_signal(&item_available);
    pthread_mutex_unlock(&m);
}

void consumer(void) 
{
    pthread_mutex_lock(&m);
    while (items_in_buffer == 0)
        pthread_cond_wait(&item_available, &m);
    /* Consume item */
    items_in_buffer--;
    pthread_cond_signal(&space_available);
    pthread_mutex_unlock(&m);
}

int main(void) {
    init();
}
