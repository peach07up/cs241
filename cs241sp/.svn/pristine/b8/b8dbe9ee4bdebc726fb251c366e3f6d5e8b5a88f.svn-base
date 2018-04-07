/**
 * Chatroom Lab
 * CS 241 - Spring 2016
 */
// gcc client.c -w -std=gnu99 -pthread -o client
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#include "chat_window.h"
#include "utils.h"

// This is useful
typedef struct info_t {
  char *host;
  char *port;
  char *username;
} info_t;

int serverSocket;

struct addrinfo hints, *result;
pthread_t threads[2];
void *writeVal, *readVal;

void close_client() {
  pthread_cancel(threads[0]);
  pthread_join(threads[0], &writeVal);
  pthread_cancel(threads[1]);
  pthread_join(threads[1], &readVal);
  // BE SURE TO CLOSE THE SOCKET
}

void *run_client(void *information) {
  /*QUESTION 1*/
  /*QUESTION 2*/
  /*QUESTION 3*/

  /*QUESTION 4*/
  /*QUESTION 5*/

  /*QUESTION 6*/

  /*QUESTION 7*/

  // Now that a connection has ben established, we can start sending data to the
  // server.
  return 0;
}
