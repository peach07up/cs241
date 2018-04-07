/* 
 * To compile this example: gcc -lpthread ...
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define NUM_THREADS 2
#define ITERATIONS_PER_THREAD 50000

int cnt = 0;

void * worker( void *ptr )
{
    int i;
    for (i = 0; i < ITERATIONS_PER_THREAD; i++)
        cnt++;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int i, result;

    /* Start threads */
    for (i = 0; i < NUM_THREADS; i++) {
        result = pthread_create(&threads[i], NULL, worker, NULL);
        assert(result == 0);
    }

    /* Wait for threads to finish */
    for (i = 0; i < NUM_THREADS; i++) {
        result = pthread_join(threads[i], NULL);
        assert(result == 0);
    }

    /* Print result */
    printf("Final value: %d (%.2f%%)\n", cnt, 100.0 * cnt / (NUM_THREADS * (double)ITERATIONS_PER_THREAD));
}
