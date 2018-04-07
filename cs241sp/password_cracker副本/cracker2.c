/**
 * Machine Problem: Password Cracker
 * CS 241 - Spring 2016
 */

#include "cracker1.h"
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
    int success;
    int failure;
} Result;

typedef struct{
    Queue *q;
    int threadId;
} Task;

int try_password(struct crypt_data *cdata, char *guess, char *hash);
int password_guess(struct crypt_data *cdata, char *password, char *hash, int start, int *guesses);
void *crack_password(void *arg);

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
    
    double startTime = getTime();
    double startCpuTime = getCPUTime();
    
    Queue queue;
    Queue_init(&queue, 100);
    
    char *username = malloc(sizeof(char) * 8);
    char *hash = malloc(sizeof(char) * 13);
    char *partial_password = malloc(sizeof(char) * 8);
    Crack *crack;
    
    while(fscanf(stdin, "%s %s %s ", username, hash, partial_password) == 3)
    {
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
        
        Queue_push(&queue, crack);
        
        username = malloc(sizeof(char) * 8);
        hash = malloc(sizeof(char) * 13);
        partial_password = malloc(sizeof(char) * 8);
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
        tasks[i].threadId = i;
        pthread_create(&pthr[i],NULL,crack_password,&tasks[i]);//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        //void *(*start_routine) (void *), void *arg);
    }
    
    void *r = NULL;
    Result *ret;
    int success = 0;
    int failure = 0;
    for(unsigned i = 0; i < thread_count ; i ++){
        pthread_join(pthr[i], &r);//int pthread_join(pthread_t thread, void **retval);
        ret = (Result *)r;
        success += ret->success;
        failure += ret->failure;
        free(ret);
    }// Join Here
    
    free(pthr);
    free(tasks);
    
    double timeElapsed = getTime() - startTime;
    double totalCpuTime = getCPUTime() - startCpuTime;
    
    v1_print_summary(success, failure, timeElapsed, totalCpuTime);
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
int password_guess(struct crypt_data *cdata, char *password, char *hash, int start, int *guesses)
{
    /*int guess = 0;
     for(char i = 'a'; i <= 'z'; i++)
     {
     password[start] = i;
     if(start < (int)strlen(password) - 1)
     {
     guess = password_guess(cdata, password, hash, start + 1, guesses);//recursive case
     }
     if(start == (int)strlen(password) - 1)
     {
     (*guesses)++;
     if(try_password(cdata, password, hash))//base case
     {
     return 1;
     }
     }
     if(guess)
     {
     return 1;
     }
     }
     return 0;*/
    
    // Set all the dots to a
    setStringPosition(&(password[start]), 0);
    (*guesses)++;
    // Try the password with all as
    while(!try_password(cdata, password, hash))
    {
        // Change the password in sequence, if == 0 it means it hit ...zzz..
        // So we failed
        if(incrementString(&(password[start])) == 0)
        {
            return 0;
        }
        (*guesses)++;
    }
    return 1;
}

void *crack_password(void *arg)
{
    Task *task = (Task *)arg;
    Queue *q = task->q;
    Result *ret = malloc(sizeof(Result));
    ret->success = 0;
    ret->failure = 0;
    
    Crack *crack;
    
    while(q->size > 0)
    {
        crack = Queue_pull(q);
        struct crypt_data cdata;
        cdata.initialized = 0;
        double startTime = getTime();
        char password[8];
        password[0] = '\0';
        
        v1_print_thread_start(task->threadId, crack->username);
        
        strcat(password, crack->partial_password);
        
        int start = (int)strlen(password) - crack->remaining_length;
        int guesses = 0;
        
        int result = password_guess(&cdata, password, crack->hash, start, &guesses);
        
        // Set 1 to 0 and 0 to 1, because for us, 1 is success but for printing 0 is success
        result = 1 - result;
        // Now password is equal to the correct password
        // Do what we need to do for the print out of the password
        
        double timeElapsed = getTime() - startTime;
        
        v1_print_thread_result(task->threadId, crack->username, password, guesses, timeElapsed, result);
        
        if(result == 0)
        {
            ret->success++;
        }
        else
        {
            ret->failure++;
        }
        
        free(crack->username);
        free(crack->hash);
        free(crack->partial_password);
        free(crack);
    }
    
    return ret;
}