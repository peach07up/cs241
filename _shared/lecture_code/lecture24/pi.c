       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define RADIUS (0xfff)

void montecarlo() {
   int inside;
   int count = 0;
   int iterations = 1000000;
   while(count ++ <iterations) {
     int x = random() & RADIUS;
     int y = random() & RADIUS;
     if( x*x + y*y <= RADIUS * RADIUS) inside++;
   }
   double pi = 4* inside / ((double)iterations);
   printf("Pi is %g\n", pi);
}

int main(int argc, char**argv) {
// srandomdev();
 unsigned int seed;
 int fd=open("/dev/random",O_RDONLY);
 read(fd, &seed, sizeof(seed));
 close(fd);
 srandom(seed);
 montecarlo();
 return 0;
} 
