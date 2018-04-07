/* This program illustrates mmap with a pair of processes.
 * A "writer" process sends messages to a "reader" process.
 *
 * After you compile this code, you should create a file for it to
 * use as its shared, mmapped file.  Edit a text file, say "mmap.txt",
 * and put at least 20 characters into it. This ensures that we'll be
 * able to see the edits in the file on disk.  (Obviously, we could
 * have done that automatically...)
 *
 * Then you can run the program by opening two terminal windows, and typing
 *
 *     ./27-mmap mmap.txt read
 *
 * into one window, and
 *
 *     ./27-mmap mmap.txt write
 *
 * into the other.  Then you can begin typing messages into the "write"
 * process, of length up to 20 characters, to be delivered to the
 * "read" process.
 *
 * You can look at the file with a text editor and see that the "writer"
 * has actually modified it on disk.
 *
 * SOMETHING TO THINK ABOUT:  The reader and writer are accessing
 * shared memory.  Could they ever interfere with each other?  How
 * could you fix it?
 *
 * NOTE: Like the code in lecture, this code omits error checks when
 * calling the various library and system calls.  Your MP code should
 * check for errors.  We omit it here so that the main steps of the
 * code are more clearly illustrated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

static const int MAX_INPUT_LENGTH = 20;

int main(int argc, char** argv) {
    int    fd;
    char * shared_mem;
    fd = open(argv[1], O_RDWR | O_CREAT);
    shared_mem = mmap(NULL, MAX_INPUT_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    if (!strcmp(argv[2], "read")) {
        while (1) {
            shared_mem[MAX_INPUT_LENGTH-1] = '\0';
            printf("%s", shared_mem);
            sleep(1);
        }
    }

    else if (!strcmp(argv[2], "write"))
        while (1) {
            fgets(shared_mem, MAX_INPUT_LENGTH, stdin);
            // msync(shared_mem, MAX_INPUT_LENGTH, MS_SYNC);
        }

    else
        printf("Unrecognized command\n");
}
