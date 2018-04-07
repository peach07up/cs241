#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/mman.h>

pid_t child;

int main() {
 int fd = open("alice.txt", O_RDONLY);
 char *ptr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_FILE|MAP_SHARED, fd, 0);
 if(ptr == (void*)-1) {perror("mmap failed"); exit(1);}

 if( (child=fork()) ==0) {
  strcpy(ptr, "'Twas brillig, and the slithy toves\nDid gyre...\n");
  exit(0);
 }
 
 waitpid(child,NULL,0);
 puts(ptr);
 return 0;
}


