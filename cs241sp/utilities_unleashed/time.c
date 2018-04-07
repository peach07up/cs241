#define _GNU_SOURCE

#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "format.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_time_usage();
    }
    
    char **child_args = malloc(sizeof(char*) * argc);
    for (int i = 0; i < argc - 1; i++) {
        int len = strlen(argv[i + 1]) + 1;
        char *arg = malloc(len);
        memcpy(arg, argv[i + 1], len);
        child_args[i] = arg;
    }
    child_args[argc - 1] = NULL;
    
    struct timespec start_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    pid_t child_pid = fork();
    if (child_pid == -1) {
        print_fork_failed();
    } else if (child_pid == 0) {
        // Execute child program.
        execvp(child_args[0], child_args);
        print_exec_failed();
    }
    
    int status;
    wait(&status);
    
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    
    int64_t duration_us = (end_time.tv_sec - start_time.tv_sec) * 1000000L +
    (end_time.tv_nsec - start_time.tv_nsec) / 1000L;
    double duration_secs = ((double)duration_us) / 1000000.0;
    display_results(argv, duration_secs);
    
}