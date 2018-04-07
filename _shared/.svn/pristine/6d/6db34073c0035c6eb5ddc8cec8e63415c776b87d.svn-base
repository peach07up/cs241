#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int counter;

void* friday( void* p) {
  printf("My pointer %p points to %s\n", p, p);

  int i = 5;
  while(i) {
   printf("%d\n",i);
   sleep(1);counter++; i--;
  }
  printf("Finished!\n");
  // Calling pthread exit at the end of the thread's
  // start routine is equivalent to return-ing.
  // pthread_exit( (void*) 0xbaadf00f ); <-- Exit value seen by pthread_join
  // ... (pthread_exit NEVER returns so actually this next line would never be executed)
  return (void*) 0xbaadf00f; // <-- Exit value seen by pthread_join
}

int main() {
  pthread_t tid;
  pthread_create( &tid , NULL, friday, "Banana");

  friday("Hello");

  void* result;
  pthread_join( tid , &result);
  printf("Thread Result is %p\n", result);

  printf("Counter is %d\n", counter);
  return 0;
}
