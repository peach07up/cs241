/**
 * Parallelized Poisson Problems
 * CS 241 - Spring 2016
 */
#include "barrier.h"

// The returns are just for errors if you want to check for them.
int barrier_destroy(barrier_t *t) {
    pthread_cond_broadcast(&(t->cv));
    pthread_cond_broadcast(&(t->cv2));
    pthread_mutex_unlock(&(t->mtx));
    pthread_mutex_unlock(&(t->mtx2));
    int error = 0;
    return error;
}

int barrier_init(barrier_t *t, unsigned n) {
    t->n_threads = n;
    t->count = n;
    t->times_used = 0;
    pthread_mutex_init(&(t->mtx), NULL);
    pthread_mutex_init(&(t->mtx2), NULL);
    pthread_cond_init(&(t->cv), NULL);
    pthread_cond_init(&(t->cv2), NULL);
    int error = 0;
    return error;
}

int barrier_wait(barrier_t *t) {
    pthread_mutex_lock(&(t->mtx));
    t->count--;
    if(t->count == 0)
    {
        t->times_used = 0;
    }
    while (t->count != 0) {
        pthread_cond_wait(&(t->cv), &(t->mtx));
    }
    pthread_cond_signal(&(t->cv));
    pthread_mutex_unlock(&(t->mtx));
    
    pthread_mutex_lock(&(t->mtx2));
    t->times_used++;
    if(t->times_used == t->n_threads)
    {
        t->count = t->times_used;
    }
    while (t->times_used != t->n_threads) {
        pthread_cond_wait(&(t->cv2), &(t->mtx2));
    }
    pthread_cond_signal(&(t->cv2));
    pthread_mutex_unlock(&(t->mtx2));
    return 0; 
    
}