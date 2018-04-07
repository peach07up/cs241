/* Example code for spawning threads to compute in parallel.
 * This is not a particularly great primality testing algorithm,
 * but it demonstrates use of threads and speeding up computation
 * via concurrency.
 * 
 * Big primes to try:
 * 3475385758524527
 * 37124508045065437
 * 394906913903735329
 * 4185296581467695669
 *
 * Composites:
 * 4153748658054516049
 * 9223372036854775807 <--- long long max value
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <limits.h>

typedef struct tester_args_t {
    long long num;
    long long first;
    long long last;
} tester_args_t;

typedef struct tester_result_t {
    long long factor;
} tester_result_t;

void* tester(void* _args) {
    tester_args_t* args = (tester_args_t*) _args;
    tester_result_t* result = (tester_result_t*) malloc(sizeof(tester_result_t));
    long long i;
    
    printf("Thread started! checking %lld through %lld\n", args->first, args-> last);
    
    result->factor = -1;
    for (i = args->first; i <= args->last; i++) {
        if (args->num % i == 0) {
            result->factor = i;
            break;
        }
    }
    return result;
}

int main(int argc, char** argv) {
    int num_threads = 1;
    long long num;

    /* I'D LIKE TO HAVE AN ARGUMENT, PLEASE */
    if (argc < 2 || argc  > 3) {
        fprintf(stderr, "Usage: %s <n> <#threads>\n", argv[0]);
        exit(1);
    }
        
    num = atoll(argv[1]);
    if (num < 0) {
        fprintf(stderr, "Overflow? Largest value I can handle = %lld\n", LLONG_MAX);
        exit(1);
    }
    if (argc == 3)
        num_threads = atoi(argv[2]);
    long long min = 2;
    long long max = 1.0 + sqrt(num);
    long long work_per_thread = 1 + ((max - min) / num_threads);

    /* START THREADS */
    pthread_t*     thread_ids  = (pthread_t*) malloc(num_threads * sizeof(pthread_t));
    tester_args_t* args_arr    = (tester_args_t*) malloc(num_threads * sizeof(tester_args_t));
    int i;

    for (i = 0; i < num_threads; i++) {
        /* Set up attributes */
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        
        /* Set up arguments */
        args_arr[i].num   = num;
        args_arr[i].first = min + i * work_per_thread;
        args_arr[i].last  = min + (i+1) * work_per_thread - 1;

        /* Create it! */
        pthread_create(&thread_ids[i], &attr, tester, &args_arr[i]);
    }

    /* COLLECT RESULTS */
    for (i = 0; i < num_threads; i++) {
        tester_result_t* result;
        pthread_join(thread_ids[i], (void**) &result);
        if (result->factor > 0) {
            printf("COMPOSITE: %lld = %lld * %lld\n", num, result->factor, num / result->factor);
            free(result);
            break;
        }
        free(result);
    }
    
    if (i == num_threads)
        printf("PRIME\n");
    
    free(thread_ids);
    free(args_arr);
    return 0;
}
