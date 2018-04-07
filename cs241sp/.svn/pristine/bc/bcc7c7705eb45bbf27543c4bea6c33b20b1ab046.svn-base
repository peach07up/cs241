/**
 * Machine Problem: Password Cracker
 * CS 241 - Spring 2016
 */

#include "cracker2.h"
#include "string.h"
#include "libs/utils.h"
#include "libs/format.h"
#include "stdio.h"
#include "stdlib.h"
#include "libs/queue.h"
#include "crypt.h"

typedef struct {
    char *username;
    char *hash;
    char *partial_password;
    int remaining_length;
} Crack;

typedef struct{
    int result;
    int guesses;
    char *username;
    char *correct_password;
} Result;

typedef struct{
    Queue *q;
    int threadId;
    int threadCount;
} Task;

typedef struct barrier_t {
    pthread_mutex_t mtx;
    pthread_cond_t cv;
    pthread_mutex_t mtx2;
    pthread_cond_t cv2;
    // Total number of threads
    unsigned n_threads;
    // Increasing or decreasing count
    unsigned count;
    unsigned int times_used;
} barrier_t;

int barrier_destroy(barrier_t *barrier);
int barrier_init(barrier_t *barrier, unsigned num_threads);
int barrier_wait(barrier_t *barrier);

int try_password(struct crypt_data *cdata, char *guess, char *hash);
int password_guess(struct crypt_data *cdata, char *password, char *hash, int start, int *guesses, size_t thread_count, int thread_id, char *username);
void *crack_password(void *arg);

pthread_mutex_t complete_mt = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t result_mt = PTHREAD_MUTEX_INITIALIZER;
int complete = 0;
Result *results;
barrier_t barrier;

int barrier_destroy(barrier_t *t) {
    pthread_cond_broadcast(&(t->cv));
    pthread_cond_broadcast(&(t->cv2));
    pthread_mutex_unlock(&(t->mtx));
    pthread_mutex_unlock(&(t->mtx2));
    int error = 0;
    return error;
}

int barrier_init(barrier_t *t, unsigned n) {
    t->n_threads = n;
    t->count = n;
    t->times_used = 0;
    pthread_mutex_init(&(t->mtx), NULL);
    pthread_mutex_init(&(t->mtx2), NULL);
    pthread_cond_init(&(t->cv), NULL);
    pthread_cond_init(&(t->cv2), NULL);
    int error = 0;
    return error;
}

int barrier_wait(barrier_t *t) {
    pthread_mutex_lock(&(t->mtx));
    t->count--;
    if(t->count == 0)
    {
        t->times_used = 0;
    }
    while (t->count != 0) {
        pthread_cond_wait(&(t->cv), &(t->mtx));
    }
    pthread_cond_signal(&(t->cv));
    pthread_mutex_unlock(&(t->mtx));
    
    pthread_mutex_lock(&(t->mtx2));
    t->times_used++;
    if(t->times_used == t->n_threads)
    {
        t->count = t->times_used;
    }
    while (t->times_used != t->n_threads) {
        pthread_cond_wait(&(t->cv2), &(t->mtx2));
    }
    pthread_cond_signal(&(t->cv2));
    pthread_mutex_unlock(&(t->mtx2));
    return 0;
    
}


int start(size_t thread_count) {
    // your code here
    // make sure to make thread_count threads
    
    /*typedef struct {
     char *username;
     char *hash;
     char *partial_password;
     int remaining_length;
     int threadId;
     } Crack;*/
    
    // Input Format
    // donna xxC4UjY9eNri6 hello...
    // We want %s %s %s, username, hash, partial_password
    // Then we want to count partial_password for .'s to get remaining_length
    
    // malloc Crack
    // malloc the username, hash and partial_password in Crack
    // Send that to fscanf
    // Keep looping while fscanf returns 3
    
    // Strategy:
    // 1. Read the input file from stdin
    // 2. Parse all the lines into Crack structures
    // 3. Make a for loop creating the threads
    // 4. If there are still passwords to crack left, join the threads and run them again
    // 5. Print out the summary
    
    // Set up the barrier for each thread, plus this one
    barrier_init(&barrier, thread_count + 1);
    
    Queue queue;
    Queue_init(&queue, 100);
    
    Queue usernames;
    Queue_init(&usernames, 100);
    
    char *username = malloc(sizeof(char) * 8);
    char *hash = malloc(sizeof(char) * 13);
    char *partial_password = malloc(sizeof(char) * 8);
    Crack *crack;
    // Keep track of the number of passwords we use
    int number_of_passwords = 0;
    char failed_password[1] = "";
    char line[500];
    
    while(fgets(line, 500, stdin) != NULL)
    {
        if(sscanf(line, "%s %s %s ", username, hash, partial_password) != 3)
        {
            return 1;
        }
        crack = malloc(sizeof(Crack));
        crack->username = username;
        crack->hash = hash;
        crack->partial_password = partial_password;
        
        // Here, check partial_password so we can fill in remaining_length
        int remaining_length = 0;
        for(unsigned i = 0; i < strlen(crack->partial_password);i++){
            if(partial_password[i] == '.'){
                remaining_length++;
            }
        }
        crack->remaining_length = remaining_length;
        
        // We want to push a copy of the password for each thread
        for(int i = 0; i < (int)thread_count; i++)
        {
            if (i > 0)
            {
                username = malloc(sizeof(char) * 8);
                hash = malloc(sizeof(char) * 13);
                partial_password = malloc(sizeof(char) * 8);
                
                strcpy(username, crack->username);
                strcpy(hash, crack->hash);
                strcpy(partial_password, crack->partial_password);
                crack = malloc(sizeof(Crack));
                crack->username = username;
                crack->hash = hash;
                crack->partial_password = partial_password;
                crack->remaining_length = remaining_length;
            }
            Queue_push(&queue, crack);
        }
        username = malloc(sizeof(char) * 8);
        strcpy(username, crack->username);
        Queue_push(&usernames, username);
        
        username = malloc(sizeof(char) * 8);
        hash = malloc(sizeof(char) * 13);
        partial_password = malloc(sizeof(char) * 8);
        number_of_passwords++;
    }
    
    
    // Initialize the results array
    results = malloc(sizeof(Result) * number_of_passwords);
    for(int i = 0; i < number_of_passwords; i++)
    {
        username = Queue_pull(&usernames);
        // Set everything to failure at first
        results[i].result = 2;
        results[i].username = username;
        results[i].correct_password = failed_password;
        results[i].guesses = 0;
    }
    
    
    // Remember to create a pthread_t array, malloced with thread_count size
    // Create thread_count number of pthreads
    // Run crack_password in all threads
    // Pass queue as the parameter in pthread_create
    // Then join all the threads, get all the Result structures that are returned
    // Add up all the success and failure numbers in the structures
    pthread_t *pthr = malloc(thread_count*sizeof(pthread_t));
    Task *tasks = malloc(thread_count * sizeof(Task));
    for(unsigned i = 0; i < thread_count ; i ++){
        tasks[i].q = &queue;
        tasks[i].threadId = i + 1;
        tasks[i].threadCount = thread_count;
        pthread_create(&pthr[i],NULL,crack_password,&tasks[i]);//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        //void *(*start_routine) (void *), void *arg);
    }
    
    
    v2_print_start_user(username);
    barrier_wait(&barrier);
    
    double startTime;
    double startCpuTime;
    startTime = getTime();
    startCpuTime = getCPUTime();
    
    int results_gathered = 0;
    while(results_gathered < number_of_passwords)
    {
        // This thread and all the crack_password threads have to barrier_wait
        // Until this proceeds
        barrier_wait(&barrier);
        
        double timeElapsed = getTime() - startTime;
        double totalCpuTime = getCPUTime() - startCpuTime;
        
        // So now, we will have gathered the correct username and password
        // If possible
        
        v2_print_summary(results[results_gathered].username,
                         results[results_gathered].correct_password,
                         results[results_gathered].guesses,
                         timeElapsed, totalCpuTime,
                         results[results_gathered].result);
        
        free(results[results_gathered].username);
        if(results[results_gathered].result == 0)
        {
            free(results[results_gathered].correct_password);
        }
        
        results_gathered++;
        
        if(results_gathered < number_of_passwords)
        {
            v2_print_start_user(results[results_gathered].username);
            barrier_wait(&barrier);
            startTime = getTime();
            startCpuTime = getCPUTime();
        }
    }
    
    for(unsigned i = 0; i < thread_count ; i ++){
        pthread_join(pthr[i], NULL);//int pthread_join(pthread_t thread, void **retval);
    }// Join Here
    free(results);
    free(pthr);
    free(tasks);
    return 0;
}

// First we have a hash
// Then we randomly guess a password
// Now we calculate hash(random_password)
// If hash(random_password) = hash, Then random_password is the password
// otherwise we randomly guess another different password and try again

// We normally guess in a standard way to make it easier to keep track
// aaaaaaaa, then aaaaaaab, then aaaaaaac all the way until zzzzzzzz

int try_password(struct crypt_data *cdata, char *guess, char *hash)
{
    if(strcmp(crypt_r(guess, "xx", cdata), hash) == 0)
    {
        return 1;
    }
    return 0;
}

// Here is the recursive algorithm for password_guess
// First start at the first letter to guess
// Set it to a
// Now call this function again, but have it start at the next letter
// That gets set to a
// All the way until we are at the end, then we guess aaa for 3 letters for example
// If that doesn't work, the last function keeps looping
// aab, aac, aad until aaz
// If that doesn't work, it returns 0
// The function one up, now tries the next letter
// ab
// It once again calls the last function to try the last letter
// aba, abb, abc ... abz
// Keeps going until azz, then it goes back one function and loops to try
// baa, bab etc...
// Eventually we'll find the right combination and return
int password_guess(struct crypt_data *cdata, char *password, char *hash, int start, int *guesses, size_t thread_count, int thread_id, char *username)
{
    int unknown_letter_count = strlen(password) - start;
    //size_t thread_count,
    //int thread_id,
    long start_index;// = start;
    long count;// = strlen(password);
    getSubrange(unknown_letter_count,thread_count,thread_id, &start_index, &count);
    
    /* Compute the subrange on which each thread should work.
     * unknown_letter_count - The number of letters in the password that are not
     * known.
     * thread_count - The number of worker threads.
     * thread_id - My thread ID, where the IDs start at 1.
     * start_index - (output parameter) This will be set to the index of
     * the first possible password this thread should try.
     * count - (output parameter) This will be set to the number of
     * passwords this thread should try.
     */
    
    // Set all the dots to a
    // The second parameter, 0, is how many times setStringPosition calls
    // incrementString first
    // This is the start
    setStringPosition(&(password[start]), start_index);
    
    // OPTION #2
    
    
    v2_print_thread_start(thread_id, username, start_index, password);
    
    // OPTION #2
    
    
    //setStringPosition(&(password[start]), 0);
    (*guesses)++;
    // Try the password with all as
    while(!try_password(cdata, password, hash))
    {
        // Change the password in sequence, if == 0 it means it hit ...zzz..
        // So we failed
        if(incrementString(&(password[start])) == 0 || *guesses == count)
        {
            // This is the end
            return 2;
        }
        (*guesses)++;
        // Check the Flag
        pthread_mutex_lock(&complete_mt);
        if(complete)
        {
            pthread_mutex_unlock(&complete_mt);
            return 1;
        }
        pthread_mutex_unlock(&complete_mt);
    }
    // Set the Flag
    pthread_mutex_lock(&complete_mt);
    complete = 1;
    pthread_mutex_unlock(&complete_mt);
    return 0;
}

void *crack_password(void *arg)
{
    Task *task = (Task *)arg;
    Queue *q = task->q;
    
    Crack *crack;
    int index = 0;
    
    while(q->size > 0)
    {
        if(task->threadId == 1)
        {
            complete = 0;
        }
        barrier_wait(&barrier);
        crack = Queue_pull(q);
        struct crypt_data cdata;
        cdata.initialized = 0;
        char *password = malloc(sizeof(char) * 8);
        password[0] = '\0';
        
        strcat(password, crack->partial_password);
        
        int start = (int)strlen(password) - crack->remaining_length;
        int guesses = 0;
        
        int result = password_guess(&cdata, password, crack->hash, start, &guesses, task->threadCount, task->threadId, crack->username);
        
        // Now password is equal to the correct password
        // Do what we need to do for the print out of the password
        
        pthread_mutex_lock(&result_mt);
        v2_print_thread_result(task->threadId, guesses, result);
        
        if(result == 0)
        {
            results[index].correct_password = password;
            results[index].result = result;
        }
        results[index].guesses += guesses;
        pthread_mutex_unlock(&result_mt);
        
        if(result != 0)
        {
            free(password);
        }
        
        free(crack->username);
        free(crack->hash);
        free(crack->partial_password);
        free(crack);
        index++;
        barrier_wait(&barrier);
    }
    
    return NULL;
}

