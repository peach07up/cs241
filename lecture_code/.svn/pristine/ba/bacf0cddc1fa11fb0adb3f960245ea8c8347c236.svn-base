#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int counter;

void* friday(void*ptr) {
  printf("My pointer at %p points to %s\n", ptr, ptr);


  int i = 5;
  while(i) { printf("%d\n", i);
     i--; sleep(1); counter ++;}
  pthread_exit( (void*) 0xbaadf00f );
  *(int*)0 = 0;
  return (void*) 0x12345678;
}

int main() {
  pthread_t tid;
  pthread_create( &tid, NULL, friday , "Banana");

//   friday("Hello");

void * result;
  pthread_join( tid , & result);

  printf("Counter is %d and the exit value is %p \n", counter, result);
 return 0;
}
