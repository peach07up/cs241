/**
 * Chatroom Lab
 * CS 241 - Spring 2016
 */
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "server.h"

void *processClient(void *arg);
void write_to_clients(const char *message, int len);

int endingServer;
int serverSocket;
int clients[MAX_CLIENTS];
int clientsConnected;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void close_server() {
  // Use a signal handler to call this function and close the server
}

int main(int argc, char **argv) {
  /*QUESTION 1*/
  /*QUESTION 2*/
  /*QUESTION 3*/

  /*QUESTION 8*/

  /*QUESTION 4*/
  /*QUESTION 5*/
  /*QUESTION 6*/

  /*QUESTION 9*/

  /*QUESTION 10*/

  // Can now start accepting and processing client connections
  /*QUESTION 11*/
}

// DO NOT MODIFY THIS FUNCTION
void write_to_clients(const char *message, int len) {
  int i;
  for (i = 0; i < clientsConnected; i++) {
    write(clients[i], message, len);
  }
}

// DO NOT MODIFY THIS FUNCTION (BUT DO USE IT)
void *processClient(void *arg) {
  int client_fd = (intptr_t)arg;
  int client_is_connected = 1;
  while (client_is_connected) {

    char buffer[MSG_SIZE];
    int len = 0;
    int num;

    // Read until client sends eof or \n is read
    while (1) {
      num = read(client_fd, buffer + len, MSG_SIZE);
      len += num;

      if (!num) {
        client_is_connected = 0;
        break;
      }
      if (buffer[len - 1] == '\n')
        break;
    }

    // Error or client closed the connection, so time to close this specific
    // client connection
    if (!client_is_connected) {
      printf("User %d left\n", client_fd);
      break;
    }

    write_to_clients(buffer, len);
  }

  close(client_fd);
  pthread_mutex_lock(&mutex);
  clientsConnected--;
  pthread_mutex_unlock(&mutex);
  return NULL;
}
