/**
 * MapReduce
 * CS 241 - Spring 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

void usage() {
    fprintf(stderr, "shuffler destination1 destination2 ...\n");
    fprintf(stderr, "where destination1..n are files on the filesystem to which "
            "the shuffler will write its output\n");
}

int main(int argc, char *argv[]) {
    // read from stdin
    // hash the key for the input line
    // send them to the correct output file (output files are given as command
    // line arguments
    if (argc < 2) {
        usage();
        exit(1);
    }
    
    // Open up all the files listed in argv
    int num_files = argc - 1;
    FILE **files = malloc(sizeof(FILE *) * num_files);
    for(int i = 1; i < num_files+1; i++)
    {
        files[i-1] = fopen(argv[i], "w");
    }
    
    // Read from stdin
    size_t n = 1024;
    char *buffer = malloc(sizeof(char) * n);
    char *key;
    char *value;
    
    while(getline(&buffer, &n, stdin) > 0)
    {
        // Use the split key value function from common to get key and value
        split_key_value(buffer, &key, &value);
        
        // Get the correct output file
        // hashKey % num_files will distribute the key towards all the files
        // Code is given in assignment
        FILE *f = files[hashKey(key) % num_files];
        
        fprintf(f, "%s: %s\n", key, value);
    }
    
    // Free memory
    for(int i = 0; i < num_files; i++)
    {
        fclose(files[i]);
    }
    free(files);
    free(buffer);
    
    return 0;
}

