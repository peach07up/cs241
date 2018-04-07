/* How much does I/O overhead matter?
 * Let's see how performance changes when we make small I/O calls,
 * compared with large ones.
 *
 * Usage:  ./copy infile outfile block_size
 *
 * Questions:
 * 1. There's one bad coding decision here that might cause
 *    us some trouble unrelated to I/O .... can you spot it?
 * 2. What happens when you run this program with a large block
 *    (buffer) size compared to a small one?
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv) {
    assert(argc == 4);
    char*  in_path = argv[1];
    char* out_path = argv[2];
    size_t bufsize = atoi(argv[3]);
    
    int  in_fd = open( in_path, O_RDONLY);
    int out_fd = open(out_path, O_WRONLY | O_CREAT, S_IRWXU);

    assert( in_fd > 0);
    assert(out_fd > 0);
    
    int done = 0;
    char buf[bufsize];

    while (! done) {
        int bytes_read = read(in_fd, buf, bufsize);
        if (bytes_read < 0 && errno == EAGAIN)
            ; /* just try again */
        else if (bytes_read <= 0)
            done = 1;
        else {
            int bytes_written = 0;
            while (bytes_written < bytes_read) {
                int written_this_time = write(out_fd, & buf[bytes_written],
                    bytes_read - bytes_written);
                if (written_this_time < 0 && errno == EAGAIN)
                    ;
                else if (written_this_time <= 0)
                    assert(0);
                else
                    bytes_written += written_this_time;
            }
        }
    }
    
    close( in_fd);
    close(out_fd);
}
