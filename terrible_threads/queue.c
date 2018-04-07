/**
 * Terrible Threads Lab
 * CS 241 - Spring 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <unistd.h>


/*
 typedef struct queue_node_t {
 
 struct queue_node_t *next;
 void *data;
 } queue_node_t;
 
 typedef struct {
 
 queue_node_t *head, *tail;
 int size;
 int maxSize;
 pthread_cond_t cv;
 pthread_mutex_t m;
 } queue_t;
 */

/**
 *  Given data, place it on the queue.  Can be called by multiple threads.
 *  Blocks if maxSize > 0 and size >= maxSize
 */
void queue_push(queue_t *queue, void *data) {
    pthread_mutex_lock(&(queue->m));
    while((queue->size) >= (queue->maxSize) && (queue->maxSize > 0)){
        pthread_mutex_unlock(&(queue->m));
        usleep(100);
        pthread_mutex_lock(&(queue->m));
    }
    queue_node_t* temp = (queue_node_t*)malloc(sizeof(queue_node_t));
    temp->next = NULL; //since it is the last element in the queue.
    temp->data = data;
    if(queue->head == NULL)
    {
        queue->head = temp;
    }
    else
    {
        // This here is an important part
        queue->tail->next = temp;
    }
    queue->tail = temp;
    queue->size ++;
    pthread_mutex_unlock(&(queue->m));
}

/**
 *  Retrieve the data from the front of the queue.  Can be called by multiple
 * threads.
 *  Blocks the queue is empty
 */
void *queue_pull(queue_t *queue) {
    pthread_mutex_lock(&(queue->m));
    while(queue->size <= 0)
    {
        pthread_mutex_unlock(&(queue->m));
        usleep(100);
        pthread_mutex_lock(&(queue->m));
    }
    void * data = queue->head->data;
    queue->size --;
    // We have Head and Head->Next Here
    queue_node_t * temp = queue->head;
    queue->head = queue->head->next;
    if(queue->head == NULL)
    {
        queue->tail = NULL;
    }
    // Now Head is equal to Head->Next. Head from before is now unaccessible
    free(temp);
    pthread_mutex_unlock(&(queue->m));
    return data;
}

/**
 *  Initializes the queue
 */
void queue_init(queue_t *queue, int maxSize) {
    //queue = (queue_t*)malloc(sizeof(queue_t));
    // These should be null
    //queue->head = (queue_node_t*)malloc(sizeof(queue_node_t));
    //queue->tail = (queue_node_t*)malloc(sizeof(queue_node_t));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->maxSize = maxSize;
    
    //pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    //pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
    pthread_mutex_init(&(queue->m),NULL);
    pthread_cond_init(&(queue->cv), NULL);
}

/**
 *  Destroys the queue, freeing any remaining nodes in it.
 */
void queue_destroy(queue_t *queue) {
    free(queue->head);
    free(queue->tail);
    pthread_mutex_destroy(&(queue->m));
    pthread_cond_destroy(&(queue->cv));
    //free(queue);
}