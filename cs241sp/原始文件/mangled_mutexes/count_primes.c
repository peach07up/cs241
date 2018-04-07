/**
 * Mangled Mutexes Lab
 * CS 241 - Spring 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

/* You should create a struct that will get passed in by reference to your
 * start_routine. */

// Globals
size_t number_of_primes; // global number of primes you need to update
/* You should create a mutex for said global variable. */

/* You should create a start routine for your threads. */

// This function parses the arguments in argv.
// An error message is printed if any of the following happens:
//  An incorrect number of arguments are passed in.
//  'start', 'end', or 'num_threads' is less than 1.
//  'end' < 'start'.
// Else an array of 3 size_t elements are returned
// in the following order: 'start', 'end', 'num_threads'.
// It is the callers job to free the memory used.
size_t *arg_parse(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "usage: %s [start] [end] [num_threads]\n", argv[0]);
    exit(1);
  }

  char *endptr;
  long tokargs[3];
  for (size_t i = 0; i < sizeof(tokargs) / sizeof(tokargs[0]); i++) {
    tokargs[i] = strtol(argv[i + 1], &endptr, 10);
    if (*endptr != '\0') {
      fprintf(stderr, "Failed to convert an arugment to a long!\n");
      exit(2);
    }
    if (tokargs[i] < 1) {
      fprintf(stderr,
              "Please have all arguments be greater than or equal to 1!\n");
      exit(3);
    }
  }
  if (tokargs[1] < tokargs[0]) {
    fprintf(stderr, "Please give a valid range!\n");
    exit(4);
  }
  size_t *args = malloc(3 * sizeof(size_t));
  for (size_t i = 0; i < sizeof(tokargs) / sizeof(tokargs[0]); i++) {
    args[i] = (size_t)tokargs[i];
  }
  return args;
}

// Call on this function when you are ready to print the result.
void print_result(size_t number_of_primes, size_t start, size_t end) {
  printf("There are %zu primes between %zu and %zu inclusive\n",
         number_of_primes, start, end);
}

// Prints the number of primes
// inbetween argv[1] and argv[2] inclusive with argv[3] threads.
int main(int argc, char *argv[]) {
  /* Your implementation goes here */
  return 0;
}
