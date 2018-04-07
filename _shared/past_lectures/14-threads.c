/* To compile this exmaple: gcc -lpthread -o 14-threads 14-threads.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void * printer_thread( void *ptr );

void * printer_thread( void *ptr )
{
    int* i = (int*) ptr;
    while (1) {
        sleep(2);
        printf("Now i = %d\n", *i);
    }
}

int main(void)
{
    pthread_t thread;
    int  result;
    int i = 0;

    result = pthread_create(&thread, NULL, printer_thread, (void*) &i);
    assert(result == 0);
    while (1)
	i++;
}
