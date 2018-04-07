#ifndef OSX_SEMAPHORE_H
#define OSX_SEMAPHORE_H

#ifdef __APPLE__ 

typedef struct _mysem {
  pthread_mutex_t *m;
  pthread_cond_t *cv;
  int count; 
} mysem_t;

void mysem_init(mysem_t*s, int pshared, int value);
void mysem_wait(mysem_t*s);
void mysem_post(mysem_t*s);
void mysem_destroy(mysem_t*s);

#define sem_wait mysem_wait
#define sem_init mysem_init
#define sem_post mysem_post
#define sem_destroy mysem_destroy

#define sem_t mysem_t

#endif
#endif
