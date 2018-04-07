#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int x = 0;

void* func(void* p) {
    x++;
    printf("x is %d\n", x);
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t tid;

    if (pthread_create(&tid, NULL, func, NULL))
        exit(1);

    func(NULL);
    return 0;
}
