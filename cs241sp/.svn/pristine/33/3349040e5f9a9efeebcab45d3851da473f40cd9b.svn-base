#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

#include "format.h"

extern char **environ;

int strcmpl(char *a, char *b, int len) {
    int i;
    for (i = 0; i < len; i++) {
        int d = a[i] - b[i];
        if (d != 0) {
            return d;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        char **e = environ;
        while (*e != NULL) {
            printf("%s\n", *e);
            e++;
        }
        return 0;
    }
    
    if (argc < 3) {
        print_env_usage();
    }
    
    int num_vars = 1;
    char *c = argv[1];
    while (*c != '\0') {
        if (*c == ',') {
            num_vars++;
        }
        
        c++;
    }
    
    int num_environ = 0;
    char **e = environ;
    while (*e != NULL) {
        num_environ++;
        e++;
    }
    
    char **child_envp = malloc(sizeof(char*) * (num_vars + num_environ + 1));
    int i;
    for (i = 0; i < num_environ; i++) {
        child_envp[i] = environ[i];
    }
    
    int total_vars = num_environ;
    c = argv[1];
    while (*c != '\0') {
        char *s = c;
        while (*c != '=' && *c != '\0') {
            c++;
        }
        c++;
        // c now points to first character of value.
        char *v = c;
        
        while (*c != ',' && *c != '\0') {
            c++;
        }
        // c now points to the character after the end of the value.
        
        int val_len = c - s + 1;
        char *copy = malloc(val_len);
        memcpy(copy, s, val_len);
        copy[val_len - 1] = '\0';
        
        int i;
        int found = 0;
        for (i = 0; i < total_vars; i++) {
            if (strcmpl(s, child_envp[i], v - s) == 0) {
                // This environmental variable has the same key.
                child_envp[i] = copy;
                found = 1;
                break;
            }
        }
        
        if (found == 0) {
            child_envp[total_vars] = copy;
            total_vars++;
        }
        
        while (*c == ',') {
            c++;
        }
    }
    
    child_envp[total_vars] = NULL;
    
    pid_t child_pid = fork();
    if (child_pid == -1) {
        print_fork_failed();
    } else if (child_pid == 0) {
        // Execute child program.
        execvpe(argv[2], argv + 2, child_envp);
        // If execvpe is successful, this line will never be reached.
        // Only reached if there is an error.
        print_exec_failed();
    }
    
    int status;
    wait(&status);
}