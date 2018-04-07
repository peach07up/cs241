#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char *message="\nI`qqx!W`mdouhodr!gsnl!BR!350!\nNi!B-!xnt!mdu!ld!rdfg`tmu!ctu!ruhmm!H!`l!g`mmhof!gns!xnt \n\n";

void handler(int sig) {
 write(1,"\033[2J",4);
 char c;
 char * ptr = message;
 // decrypt and print the message
 while((c = * ptr ++ )) { c ^= !! (c & 0xe0); write( 1, &c, 1 ); }
}

int main() {
 signal(SIGINT, handler);
 printf("\033[2J\033[91m");
 for(int x = -20 ; x < 18 ; x++) { 
   for(int y=16; y > 0; y--) {
     int ax = x < 0 ? -x : x;
     printf("\033[%d;%dH%c",18-y,x+20, 32 + ( ax < y && ( y < 12 || (ax-6)*(ax-6)< 230-y*y)));
     fflush(stdout);
     usleep(5000);
   }
  }
  puts("\n\n\033[0m");
  while(1) sleep(1);
  return 0;
}
