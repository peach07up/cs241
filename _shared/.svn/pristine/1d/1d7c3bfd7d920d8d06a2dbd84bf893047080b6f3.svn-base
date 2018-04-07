/**
 * Chatroom Lab
 * CS 241 - Spring 2016
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

#define MSG_SIZE 256

int closeChat;

static WINDOW *output;
static WINDOW *input;
static WINDOW *boundary;

void close_chat() { closeChat = 1; }

void draw_border(WINDOW *screen) {
  int x, y, i;
  getmaxyx(screen, y, x);
  for (i = 1; i < (x - 1); i++) {
    mvwprintw(screen, y - 1, i, "-");
  }
}

void create_windows() {

  int parent_x, parent_y;
  int boundary_size = 2;
  initscr();
  curs_set(1); // Sets cursor visibility
  // raw();		// Removes control & interupt characaters

  // Get maximum window dimensions
  getmaxyx(stdscr, parent_y, parent_x);

  // Set up initial windows
  output = newwin(parent_y - boundary_size - 1, parent_x, 0, 0);
  input = newwin(1, parent_x, parent_y - 1, 0);
  boundary = newwin(boundary_size, parent_x, parent_y - boundary_size - 1, 0);
  // wtimeout(input,50);
  // Allow the windows to scroll
  scrollok(output, TRUE);
  scrollok(input, TRUE);

  draw_border(boundary);
  wrefresh(boundary);
}

void write_message_to_screen(const char *format, ...) {

  va_list arg;
  va_start(arg, format);
  vwprintw(output, format, arg);
  va_end(arg);
  wrefresh(output);
}

void read_message_from_screen(char **buffer) {
  if (*buffer == NULL)
    *buffer = calloc(1, MSG_SIZE);
  else
    memset(*buffer, 0, MSG_SIZE);
  wprintw(input, "> ");
  wrefresh(input);
  // char * tmp_buffer = calloc(0,MSG_SIZE);
  // int ret = wgetnstr(input, *buffer, MSG_SIZE-1);
  // handle time out
  // write to temporary buffer instead of the return one
  /*while ( wgetnstr(input, tmp_buffer, MSG_SIZE-1) == ERR ){

          if (closeChat) // if return because of interrupt, close it
                  break;
          // see if there is anything written to buffer
          int tmp_buffer_len = strlen(tmp_buffer);
          if ( tmp_buffer_len != 0 ) {
                  int buffer_len = strlen(*buffer);
                  sprintf( *buffer + buffer_len, "%s", tmp_buffer);
          }
          wprintw(input, "> %s", *buffer);
  }
  int tmp_buffer_len = strlen(tmp_buffer);
  if ( tmp_buffer_len != 0 ) {
          int buffer_len = strlen(*buffer);
          sprintf( *buffer + buffer_len, "%s", tmp_buffer);
  }*/
  wgetnstr(input, *buffer, MSG_SIZE - 1);
  if (closeChat) {
    free(*buffer);
    *buffer = NULL;
  }
}

void destroy_windows() {
  // clean up
  delwin(output);
  delwin(boundary);
  delwin(input);
  endwin();
}

// int main(int argc, char *argv[]) {

// 	create_windows();

// 	char* buffer = NULL;
// 	while ( !buffer || strcmp(buffer, "quit")){
// 		read_message_from_screen(&buffer);
// 		write_message_to_screen(buffer);
// 	}

// 	destroy_windows();
// 	return 0;
// }
