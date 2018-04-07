#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_t tid1,tid2;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int counter;
void*myfunc2(void*param) {
 int i=0; // stack variable
   pthread_mutex_lock( &m);
 for(; i < 1000000;i++) {
   counter ++;
  } 
  pthread_mutex_unlock(&m);
 return NULL;
}
int main() {
 pthread_create(&tid1, 0, myfunc2, NULL);
 pthread_create(&tid2, 0, myfunc2, NULL);
 pthread_join(tid1,NULL);
 pthread_join(tid2,NULL);
 printf("%d\n", counter );
}
