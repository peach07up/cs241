/* 
 * "Hello world" using condition variables.
 * 
 * Brighten Godfrey <pbg@illinois.edu>
 *
 * To compile:  gcc -lpthread -o 22-condition 22-condition.c
 *
 * NOTE: this example might have a bug in it.  Can you find it?
 * Also, to keep the example simple, we aren't error-checking return values
 * from the pthread calls.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

/* Global variables */
pthread_mutex_t m;
pthread_cond_t  hello_printed_event; /* Event: "Hello" was printed */
 
void init(void) {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&hello_printed_event, NULL);
}

#define some_sort_of_flush_call fflush

void* hello(void * arg) 
{
    pthread_mutex_lock(&m);
    printf("Hello "); some_sort_of_flush_call(stdout);
    pthread_cond_signal(&hello_printed_event);
    pthread_mutex_unlock(&m);
    return NULL;
}

void* world(void * arg)
{
    pthread_mutex_lock(&m);
    pthread_cond_wait(&hello_printed_event, &m);
    printf("world!\n");
    pthread_mutex_unlock(&m);
    return NULL;
}

int main(void) {
    pthread_t hello_thread, world_thread;

    init();

    pthread_create(&hello_thread, NULL, hello, NULL);
    pthread_create(&world_thread, NULL, world, NULL);
    pthread_join(hello_thread, NULL);
    pthread_join(world_thread, NULL);
}
