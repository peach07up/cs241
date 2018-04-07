#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

// http://stackoverflow.com/questions/26423537/how-to-position-the-input-text-cursor-in-c
#define clear() fprintf(stderr, "\033[H\033[J")
#define gotoxy(x,y) fprintf(stderr, "\033[%d;%dH", (x), (y))

// http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
int rows = 0;
int cols = 0;

void snowflake() {
	// Init a random number generator
	srand((unsigned)time(NULL));

	// Pick a random column
	int col = rand() % cols;

	// Sart at row 0
	int row = 0;

	// Loop as the snowflake falls one row at a time...
	while (row < rows) {
		// Write the snowflake
		gotoxy(row, col);
		fprintf(stderr, "*");

		// Sleep for a while (pause the falling)
		usleep(200000);

		// Clear the snowflake
		gotoxy(row, col);
		fprintf(stderr, " ");

		// Get ready to draw the next row
		row++;
	}
}

void main() {
	// Get the terminal window size:
	// http://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	rows = w.ws_row;
	cols = w.ws_col;

	// Clear the screen
	clear();

	// Fork a bunch
	fork();
	fork();

	snowflake();
}
