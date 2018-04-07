#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	int pfds[2];
	char buf[30];

	pipe(pfds);

    if (!fork()) {
	    printf("CHILD: writing to pipe\n");
        write(pfds[1], "test", 5);
        printf("CHILD: exiting\n");
	} else {
        printf("PARENT: reading from pipe\n");
        read(pfds[0], buf, 5);
        printf("PARENT: read \"%s\"\n", buf);

        wait(NULL);
	}

	return 0;
}




