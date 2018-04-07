#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N (20)
int admin, debug;
int histogram[N];

static int hash(char* str) {
   int c, h = 0; // sdbm hash
   while (( c = *str++))
       h = c + (h << 6) + (h << 16) - h;
   return h;
}

int main() {
  char mesg[256];
  int i = 0;
  do {
    sprintf(mesg, "CS241-%d", i);
    int h  = hash(mesg);
    if(h ==INT_MIN) printf("%s\n", mesg);
    if((i&0xffffff) ==0) printf("%p:%p\n",i,h);
  }  while(++i );
  return 0;
}

