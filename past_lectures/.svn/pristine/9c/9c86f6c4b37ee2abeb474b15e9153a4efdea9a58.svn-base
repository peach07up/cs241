/* Creates a FIFO, then reads from it as if it were stdin.
 * As usual, all error checking is omitted so it's easier to see the main ideas.
 *
 * Command line usage:  ./fifostdin /tmp/fifo.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) {
    mkfifo(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);

    int fifo = open(argv[1], O_RDONLY);

    /* Duplicate the file 'fifo', so that file descriptor 0 points to it.
     * Note that 0 is the file descriptor of stdin. */
    dup2(fifo, 0);

    char line[1024];
    while (fgets(line, 1024, stdin))
        printf("I got this: %s\n", line);
}