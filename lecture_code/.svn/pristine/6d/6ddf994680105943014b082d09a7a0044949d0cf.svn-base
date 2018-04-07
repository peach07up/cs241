// Racing Horse Barriers - a demo by L Angrave for Cs241
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
typedef struct horse_ {
	int x,y;
	char* name;
} horse_t;

void display(horse_t* horse) {
	int x = horse->x, y=horse->y;
	char* graphic = (x & 0x1)  ? "`/=\\^" :  "`|=|^";
	int color = 32+ ((y/2) & 0x3);
    fprintf(stderr, "\033[%dm\033[%d;%dH%s", color, y, x,graphic );
}

int please_stop;

int readysetgo;
horse_t* winner;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv1 = PTHREAD_COND_INITIALIZER;

void* racer(void*param) {
	horse_t* horse = (horse_t*) param;
	while(!please_stop) {
		horse->x = 0;
		
		pthread_mutex_lock(&m);		
		while(readysetgo ==0) pthread_cond_wait(&cv1,&m);
		pthread_mutex_unlock(&m);
		
		while(winner == NULL) {
		   horse->x++;
		   usleep(100000 + 10000 * (rand() % 10));
		   display(horse);
		   if(horse->x > 40) { winner = horse; pthread_cond_broadcast(&cv1); }
		}
		
		pthread_mutex_lock(&m);		
		while(readysetgo ==1) pthread_cond_wait(&cv1,&m);
		pthread_mutex_unlock(&m);	
	}
	return NULL;
}
void handlectrlc(int sig) {
	please_stop = 1;
}
int main() {
	signal(SIGINT, handlectrlc);
	#define NHORSES (4)
	pthread_t tids[NHORSES];
	horse_t horses[NHORSES];
	char *names[] = {"Ant","Bee","Cat","Dog"};
	
	
    for(int i =0; i < NHORSES; i++) {
		horses[i].y = 1+ i*2;
		horses[i].name = names[i%4];
		
     	pthread_create(tids+i, NULL, racer,horses + i);
	}
	while(!please_stop) {
		printf("\033[11;1HReady...");
		sleep(1);
		puts("Set...");
		sleep(1);
		puts("Go...");
		fprintf(stderr, "\033[2J" );
		winner = NULL;
		readysetgo = 1;
		pthread_cond_broadcast(&cv1);
	
		pthread_mutex_lock(&m);		
		while(winner == NULL) pthread_cond_wait(&cv1,&m);
		pthread_mutex_unlock(&m);
	    printf("\033[10;1H%s is the winner\n", winner->name);
	
		readysetgo = 0;
		pthread_cond_broadcast(&cv1);
	}
	return 0;
}