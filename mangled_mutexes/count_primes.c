/**
 * Mangled Mutexes Lab
 * CS 241 - Spring 2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <math.h>

/* You should create a struct that will get passed in by reference to your
 * start_routine. */
typedef struct {
    int start;
    int end;
    int total_threads;
    int thread_num;
} thread_param_t;

// Globals
size_t number_of_primes; // global number of primes you need to update
/* You should create a mutex for said global variable. */
pthread_mutex_t number_of_primes_lock = PTHREAD_MUTEX_INITIALIZER;


bool isPrime(int x){
    if (x < 2) {
        return false;
    }
    
    int sqroot = (int)sqrt((double)x);
    for(int i = 2; i <= sqroot; i ++){
        if(i * (x / i) == x) return false;//or gcd(x,i)=1?
    }
    
    return true;
}

void *thread_routine(void *arg) {
    thread_param_t *param = arg;
    for(int i = param->start;i <= param->end; i ++){
        if (i % param->total_threads == param->thread_num) {
            if(isPrime(i)) {
                pthread_mutex_lock(&number_of_primes_lock);
                number_of_primes ++;
                pthread_mutex_unlock(&number_of_primes_lock);
            }
        }
    }
    free(param);
    return (void*)NULL;
}

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
    size_t *arg  = arg_parse(argc, argv);
    pthread_t *tids = malloc(sizeof(pthread_t) * arg[2]);
    for(unsigned int i = 0; i < arg[2] ; i ++){
        thread_param_t * param = malloc(sizeof(thread_param_t));
        param->start = arg[0];
        param->end = arg[1];
        param->total_threads = arg[2] + 1;
        param->thread_num = i;
        pthread_create(&tids[i], NULL, thread_routine, param);
        //int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        //void *(*start_routine) (void *), void *arg);
    }
    
    thread_param_t * param = malloc(sizeof(thread_param_t));
    param->start = arg[0];
    param->end = arg[1];
    param->total_threads = arg[2] + 1;
    param->thread_num = arg[2];
    thread_routine(param);
    
    //Wait for both threads to finish:
    for(unsigned int i = 0; i < arg[2] ; i ++){
        pthread_join(tids[i], NULL);
    }
    free(tids);
    
    print_result(number_of_primes, arg[0], arg[1]);
    return 0; 
}

