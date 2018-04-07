/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "common.h"

void usage() {
  printf("./mr0 input_file output_file mapper_exec reducer_exec\n");
}

int main(int argc, char **argv) {
  // Open the input file.

  // Create a pipe to connect the mapper to the reducer.

  // Open the output file.

  // Start the mapper.

  // Start the reducer.

  // Wait for the reducer to finish.

  // Print nonzero subprocess exit codes.

  // Count the number of lines in the output file.

  return 0;
}
