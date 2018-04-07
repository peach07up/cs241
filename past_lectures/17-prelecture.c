/* This program spawns a thread that computes two of my favorite numbers.
 * The thread uses a structure to return more than one value.
 * Then, it gets the return value via pthread_join() and prints them out.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _favorites_t {
    double d;
    int    i;
} favorites_t;

void * get_favorites(void *arg) {
    favorites_t my_fav;
    my_fav.d = 3.14159265359;
    my_fav.i = 42;
    pthread_exit((void*)&my_fav);
}

int main(int argc, char** argv) {
    pthread_t    pid;
    favorites_t* my_fav;
    int          ret;

    if (pthread_create(&pid, NULL, get_favorites, NULL))
        exit(1);
    
    if (pthread_join(pid, (void**) &my_fav))
        exit(1);

    printf("I really like %f and %d!\n", my_fav->d, my_fav->i);

    free(my_fav);
    return 0;
}
