#include <stdio.h>
#define N (20)
int admin, debug;
int histogram[N];

static int hash(char* str) {
   int c, h = 0; // sdbm hash
   while ( (c = *str++))
       h = c + (h << 6) + (h << 16) - h;
   return h;
}

int main(int argc, char**argv){

   while(argc>1) {
      char*word= argv[ --argc];
      int h = hash(word);
      printf("%d %d \n",h, -h);
      histogram[ (h<0?-h:h) % N ] ++;
   }
   if(admin || debug) puts("Admin/Debug rights");
   return 0;
}

