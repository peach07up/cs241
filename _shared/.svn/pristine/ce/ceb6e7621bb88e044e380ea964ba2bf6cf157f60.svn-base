#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "osx_semaphore.h"
// for this demo just include the source code directly!
#include "osx_semaphore.c"

sem_t s;
pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
int remain = 5;

void* barrier(void*param) {
   pthread_mutex_lock(&m);
   remain --;
   pthread_mutex_unlock(&m);
   
   if(remain > 0)   sem_wait(&s);
   sem_post(&s);

   puts("OK Go");
   return NULL;
}

pthread_t tids[5];
int main(int argc, char**argv) {
  sem_init(&s,0,0);

  for(int i =0 ; i<5; i++) {
    usleep(5E5);
    printf("%d\n",i);
    pthread_create(tids+i, NULL, barrier, NULL);
  }
  pthread_exit(NULL);
  return 0;
}
