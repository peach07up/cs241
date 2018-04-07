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
    
    // Number of arguments wrong, print usage and exit
    if(argc != 5)
    {
        usage();
        return 0;
    }
    
    // Get the arguments
    int input = open(argv[1], O_RDONLY | O_CLOEXEC);
    int output = open(argv[2], O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC);
    char *mapper = argv[3];
    char *reducer = argv[4];
    
    // Make the Pipes
    int pipe[2];
    
    pipe2(pipe, O_CLOEXEC);
    
    // Use the provided descriptors_add function to keep track of all our
    // open files
    descriptors_add(input);
    descriptors_add(output);
    descriptors_add(pipe[0]);
    descriptors_add(pipe[1]);
    
    pid_t mapper_pid = fork();
    
    if(mapper_pid == 0)
    {
        // Replace stdin and stdout with the appropriate descriptors
        // Mapper Read to Stdin
        dup2(input, 0);
        // Reducer Write to Stdout
        dup2(pipe[1], 1);
        
        // Close every descriptor because we're done with using them
        descriptors_closeall();
        
        // We'l use execcl
        // Arguments are filename, argv[0], argv[1] etc...
        // argv[0] is the filename so we'll just reuse it and there are not other
        // argvs so thats it
        execl(mapper, mapper);
        
        // Program is now gone, replaced with the executed program
        // and wil never reach here
    }
    
    pid_t reducer_pid = fork();
    
    if(reducer_pid == 0)
    {
        dup2(pipe[0], 0);
        dup2(output, 1);
        
        descriptors_closeall();
        
        execl(reducer, reducer);
    }
    
    // Close all the descriptors, we've passed them to the processes so we
    // don't need them here anymore
    descriptors_closeall();
    
    int status = 0;
    waitpid(mapper_pid, &status, 0);
    waitpid(reducer_pid, &status, 0);
    
    // Free the memory
    descriptors_destroy();
    
    return 0;
}

