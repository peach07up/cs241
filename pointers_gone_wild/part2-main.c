/**
 * Machine Problem 0
 * CS 241 - Spring 2016
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "part2-functions.h"

/**
 * (Edit this function to print out the "Illinois" lines in
 * part2-functions.c in order.)
 */
int main() {
    first_step(81);
    
    int x = 132;
    int *p = &x;
    second_step(p);
    
    int *ds[1];
    int b;
    int * a = &b;
    *a = 8942;
    ds[0] = a;
    double_step(ds);
    
    void * ss = malloc(15*sizeof(int));//free later
    *(int*)(ss+5) = 15;
    strange_step(ss);
    
    *(char*)(ss+3) = 0;
    empty_step(ss);
    free(ss);
    
    char c[4];
    c[3] = 'u';
    void * d = (void*)c;
    two_step(d,c);
    
    three_step(c,c+2,c+4);
    
    char e[4];
    e[1] = '0';
    e[2] = '0'+ 8;
    e[3] = '0'+ 16;
    step_step_step(e,e,e);
    
    int o = '0';
    it_may_be_odd(e+(sizeof(char)), o);
    
    char st[] = "blahblah,CS241";
    tok_step(st);
    
    void * ptr;
    x = 4353;
    ptr = (void*)&x;
    the_end(ptr,ptr);
    // your code here
  return 0;
}
