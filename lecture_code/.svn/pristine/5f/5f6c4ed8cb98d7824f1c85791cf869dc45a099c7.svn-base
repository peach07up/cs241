#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

void* mymalloc(unsigned int numbytes) {
  printf("Top of heap was %p\n", sbrk(0) );

  void* ptr = sbrk(numbytes);
  if(ptr == (void*) -1) return NULL; // no mem for you!

  printf("Now you have some mem at %p\n",ptr );

  return ptr;
}

void myfree(void*mem) { if(mem) printf("Freeing %p\n",mem); }

int main() {

  char* p = mymalloc( 16 );
  strcpy(p, "Hello");
  char* p2 = mymalloc(16);
  strcpy(p2, p);
  myfree (p);
  puts(p2);
  myfree(p2);
}
