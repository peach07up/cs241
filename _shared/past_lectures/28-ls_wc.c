#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This program constructs "ls | wc -l", through a pipe:
 *
 *   stdin ---> ls ---> [pipe] ---> wc -l ---> stdout
 *
 * No arguments -- just run it.
 */


int main(void) {
    int pfds[2];

    pipe(pfds);

    if (!fork()) { /* Here we'll run ls (could have run wc, doesn't matter) */

        /* Copy the write end of the pipe (pfds[1]) into stdout's
         * file descriptor (file descriptor 1).  The old stdout
         * is closed automatically first. */
        dup2(pfds[1], 1);

        /* Don't need the read end of the pipe in this process */
        close(pfds[0]);

        /* OK - inputs/outputs are all set.  Now exec the command. */
        execlp("ls", "ls", NULL);

    } else { /* Here we'll run wc -l */

        /* Copy the read end of the pipe (pfds[0]) into stdin's
         * file descriptor (file descriptor 0).  The old stdin
         * is closed automatically first. */
        dup2(pfds[0], 0);

        /* Don't need the write end of the pipe in this process */
        close(pfds[1]);

        /* OK - inputs/outputs are all set.  Now exec the command. */
        execlp("wc", "wc", "-l", NULL);

    }
    return 0;
}
