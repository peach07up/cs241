/* Threads print stuff out continuously.  Can we see what the OS's
 * time quantum looks like?
 *
 * To compile this exmaple: gcc -lpthread ...
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct printer_arg_t {
    int thread_index;
} printer_arg_t;

#define BUF_SIZE     100
#define NUM_THREADS  2

void * printer_thread( void *ptr )
{
    /* Create the message we will print out */
    printer_arg_t* arg = (printer_arg_t*) ptr;
    char message[BUF_SIZE];
    int i;
    for (i = 0; i < BUF_SIZE; i++)
        message[i] = ' ';
    sprintf(message + 10 * arg->thread_index, "thread %d\n", arg->thread_index);

    /* Print it forever */
    while (1)
        printf("%s", message);
}

int main(void)
{
    pthread_t     thread[NUM_THREADS];
    printer_arg_t args[NUM_THREADS];
    int i, result;

    for (i = 0; i < NUM_THREADS; i++) {
        args[i].thread_index = i;
        result = pthread_create(&thread[i], NULL, printer_thread, (void*) &args[i]);
        assert(result == 0);
    }
    pthread_exit(NULL);
}
