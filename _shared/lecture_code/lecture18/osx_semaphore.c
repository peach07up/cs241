#ifdef __APPLE__

#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include "osx_semaphore.h"


void mysem_init(mysem_t*s, int pshared, int value) {
 assert(pshared == 0);

 s->m = malloc(sizeof (pthread_mutex_t));
 s->cv = malloc(sizeof (pthread_cond_t));
 pthread_mutex_init(s->m, NULL);
 pthread_cond_init(s->cv, NULL);
 s->count = value;
}

void mysem_destroy(mysem_t*s) {
   free(s->m); s->m = NULL;
   free(s->cv); s->cv = NULL;
   free(s);
}

void mysem_wait(mysem_t*s) {
  pthread_mutex_lock(s->m);
  while(s->count <=0) pthread_cond_wait(s->cv, s->m);
  s->count --;
  pthread_mutex_unlock(s->m);
}

void mysem_post(mysem_t*s) {
  pthread_mutex_lock(s->m);
  s->count ++;
  if(s->count ==1) pthread_cond_signal(s->cv);
  pthread_mutex_unlock(s->m);
}

#endif
