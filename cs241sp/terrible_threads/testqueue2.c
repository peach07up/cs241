#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"


int main(void)
{
    queue_t testQueue;
    // printf("Run\n");
    queue_init(&testQueue, 200);
    // printf("Queue Ini\n");
    
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    
    queue_push( &testQueue, &a );
    queue_push( &testQueue, &b );
    queue_push( &testQueue, &c );
    
    queue_push( &testQueue, &d );
    queue_push( &testQueue, &e );
    queue_push( &testQueue, &e );
    
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    
    
    queue_push( &testQueue, &a );
    queue_push( &testQueue, &b );
    queue_push( &testQueue, &c );
    
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    
    
    queue_push( &testQueue, &a );
    queue_push( &testQueue, &b );
    queue_push( &testQueue, &c );
    
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    printf("%d", *((int *)queue_pull( &testQueue)));
    
    queue_destroy(&testQueue);
    return 0;
}

