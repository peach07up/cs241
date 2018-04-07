#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Threads = "Allow two CPUs to work inside your process at the same time"
// include pthread.h
// compile with -pthread

/* 
  int pthread_create( pthread_t * thread, pthread_attr_t * attr, 
  void *(*start_routine)(void *), void * arg);

  Trick:Read a pointer to a function like a function declaration
  but the function name is surrounded with "(* ... )"
    
*/

int counter; // global

void* helloArghhh(void* ptr) {
  
  int value = (int) ptr; // will be 0x1234
  printf("I got %d\n", value);
  
  //pthread_exit((void*) 0x456); // This would cause this thread to finish!
  //puts("Never printed!"); //  pthread_exit() never returns.
  
  int i =0;
  for( ; i < 5; i++) {
    counter ++; 
    sleep(1);
  }
  return 0x789; // returns 
}

int main(int argc, char* argv[]) {
  // start another thread running in parallel to the original main thread
  pthread_t tid;
  pthread_create( &tid, NULL, helloArghhh, (void*) 0x1234 );
  // Uses &tid because p_create will write into that variable
  
  sleep(2);
  printf("Results so far %d\n", counter);
  
  void *result;
  pthread_join(tid, &result); // will wait for thread 'tid' to finish
  // Gotcha: Use 'tid' not &tid. 
  Use &result because we want to change the contents of result
  
  printf("I am the main thread and the exit value of the thread is %p\n", result); // 0x456 0x789
  while(1) {} // This thread will never finish
  
  
  return 0;
}
/*
exit() - the entire process (ie all threads) will finish
pthread_exit() - the calling thread finishes
(The process will exit if this is the last thread)

Threads will also finish if they return from their original starting function
*/
