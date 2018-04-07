#include <stdlib.h>
#include <stdio.h>
#include "mini_valgrind.h"
int main() {
    // your tests here using malloc and free
    void *data1 = malloc(10);
    void *data2 = malloc(20);
    
    free(data1);
    free(NULL);
    if (data2) { }
    
    void *data3 = malloc(30);
    free(data3);
    
    void *data4 = malloc(40);
    if (data4) { }
    
    // Do NOT modify this line
    atexit(print_report);
    return 0;
}