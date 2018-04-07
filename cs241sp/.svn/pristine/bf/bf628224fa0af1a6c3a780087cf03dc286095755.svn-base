#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NUM_THREADS 20
#define NUM_INSERTS 50

void * thread_insert(void * arg);
void * thread_remove(void * arg);

int main(void)
{
    int i;
    queue_t q;
    queue_init(&q,NUM_THREADS*NUM_INSERTS*2);
    pthread_t * insert_threads = malloc(NUM_THREADS*sizeof(pthread_t));
    pthread_t * remove_threads = malloc(NUM_THREADS*sizeof(pthread_t));
    
    for (i=0; i<NUM_THREADS; i++)
    {
        pthread_create(&insert_threads[i], NULL, thread_insert, &q);
        pthread_create(&remove_threads[i], NULL, thread_remove, &q);
        
    }
    
    void * out;
    long k = 0;
    
    for (i=0; i<NUM_THREADS; i++)
    {
        //printf("Try Join %d\n", i);
        pthread_join(insert_threads[i], &out);
        //printf("Joinned Insert\n");
        pthread_join(remove_threads[i], &out);
        // printf("Join %d, Value %d\n", i, *((int *)out));
        k += *((int *)out);
        free(out);
    }
    
    //out = thread_remove(&q);
    //printf(", Value %d\n", i, *((int *)out));
    //k += *((int *)out);
    //free(out);
    //out = thread_remove(&q);
    //printf(", Value %d\n", i, *((int *)out));
    //k += *((int *)out);
    //free(out);
    
    //printf("Before Destroy\n");
    
    
    queue_destroy(&q);
    //printf("After Destroy\n");
    if (k == NUM_INSERTS*NUM_THREADS)
        printf("Success! Data inserted and removed.\n");
    else
        printf("Failed to retrieve all inserted data!\n");
    return 0;
}


void * thread_insert(void * arg)
{
    int i;
    queue_t * q = (queue_t *) arg;
    for (i = 0; i < NUM_INSERTS; i++)
    {
        int * a = malloc(sizeof(int));
        *a = 1;
        //printf("Queue Push\n");
        queue_push(q, (void *) a);
        //printf("Pushed %d\n", *a);
    }
    return NULL;
    
}

void * thread_remove(void * arg)
{
    int i;
    int *k = malloc(sizeof(int));
    *k = 0;
    int *a;
    queue_t * q = (queue_t *) arg;
    for(i = 0; i < NUM_INSERTS; i++)
    {
        //printf("Queue Pull\n");
        a = ((int *)queue_pull(q));
        //printf("Pulled %d\n", *a);
        *k += *a;
        //printf("K %d\n", *k);
        free(a);
    }
    //printf("Value %d\n", *k);
    return (void *)k;
}

