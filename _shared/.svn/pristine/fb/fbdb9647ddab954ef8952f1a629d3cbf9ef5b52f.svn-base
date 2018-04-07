#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct link_ {
  struct link_* next;
  int value;
} link_t;

link_t* head;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* list_insert(int v) {
  link_t* link = malloc( sizeof(link_t));
  link->value = v;
  pthread_mutex_lock(&m);
  link-> next = head;
  head = link;
  pthread_mutex_unlock(&m);
  return link;
}
link_t* list_remove() {
   pthread_mutex_lock(&m);
   link_t* result = head;
   if(result) head = result->next;
   pthread_mutex_unlock(&m);
   return result;
}


void* runner(void*unused) {
  int i;
  for(i = 0; i < 1000; i++)
    list_insert(i);
  return NULL;
}

int main() {
  pthread_t tid1, tid2;
  pthread_create(&tid1, 0, runner, NULL);
  pthread_create(&tid2, 0, runner, NULL);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  int count = 0;
  while(list_remove()) {  count++;}
  printf("%d links removed\n", count);
}
