/**
 * Terrible Threads Lab
 * CS 241 - Spring 2016
 */
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include "semamore.h"

/**
 * Initializes the Semamore. Important: the struct is assumed to have been
 *malloc'ed by the user.
 * Example:
 * 	Semamore *s = malloc(sizeof(Semamore));
 * 	semm_init(s, 5, 10);
 *
 */
/*typedef struct {
 
 int value, max_val;
 
 pthread_mutex_t m;
 pthread_cond_t cv;
 
 } Semamore;*/
void semm_init(Semamore *s, int value, int max_val) {
    s = (Semamore*) malloc(sizeof(Semamore));
    s->value = value;
    s->value = max_val;
    
    //pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
    //pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
    //s->m = m;
    //s->cv = cv;
    pthread_mutex_init(&(s->m), NULL);
    pthread_cond_init(&(s->cv), NULL);
}

/**
 *  Should block when the value in the Semamore struct (See semamore.h) is at 0.
 *  Otherwise, should decrement the value.
 */

void semm_wait(Semamore *s) {
    if(s->value == 0){
        pthread_cond_wait(&(s->cv),&(s->m)); //we should block the process
    }
    else{
        s->value --;
        pthread_cond_signal(&(s->cv));
        
    }
    
}

/**
 *  Should block when the value in the Semamore struct (See semamore.h) is at
 * max_value.
 *  Otherwise, should increment the value.
 */

void semm_post(Semamore *s) {
    if(s->value == s-> max_val){
        pthread_cond_wait(&(s->cv),&(s->m));//should block when we reach the maximum value.
    }
    else{
        s->value ++;
        pthread_cond_signal(&(s->cv));
    }
}

/**
 * Takes a pointer to a Semamore struct to help cleanup some members of the
 * struct.
 * The actual Semamore struct must be freed by the user.
 */

void semm_destroy(Semamore *s) {
    //here we need to destroy members of semamore
    pthread_mutex_destroy(&(s->m));
    pthread_cond_destroy(&(s->cv));
}

