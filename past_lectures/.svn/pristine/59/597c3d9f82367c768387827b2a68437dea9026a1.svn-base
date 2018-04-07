#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>

void one(int write_fd)
{
	sleep(1);
	write(write_fd, "B", 1);
	sleep(1);
	write(write_fd, "C", 1);
	close(write_fd);
}

void two(int write_fd)
{
	write(write_fd, "A", 1);
	sleep(3);
	write(write_fd, "D", 1);

	close(write_fd);
}


void main()
{
	/* Create the epoll() */
	int epoll_fd = epoll_create(10);


	/* Launch each process */

	// Double-array of fds for the pipe() /process
	int **fds = malloc(2 * sizeof(int *));

	// A struct epoll_event for each process
	struct epoll_event event[2];

	// Create two processs...
	int i;
	for (i = 0; i < 2; i++)
	{
		// Create the pipe
		fds[i] = malloc(2 * sizeof(int));
		pipe(fds[i]);
		int read_fd = fds[i][0];
		int write_fd = fds[i][1];

		// fork():
		pid_t pid = fork();
		if (pid == 0) /* child */
		{
			// Close the end of the pipe we aren't using
			close(read_fd);

			// Run process-specific code
			if (i == 0) { one(write_fd); }
			else if (i == 1) { two(write_fd); }

			// exit() the child
			exit(0);
		}
		else if (pid > 0) /* parent */
		{
			// Close the ned of the pipe we aren't using
			close(write_fd);
		}

		// Setup the epoll_event for this process
		event[i].events = EPOLLIN;
		event[i].data.fd = read_fd;
		epoll_ctl( epoll_fd, EPOLL_CTL_ADD, read_fd, &event[i]);
	}


	/* Read data via epoll_wait() */
	while (1)
	{
		struct epoll_event ev;
		epoll_wait(epoll_fd, &ev, 1, -1);

		char c;
		ssize_t bytes = read(ev.data.fd, &c, 1);

		if (bytes == 1)
			printf("Read: %c\n", c);
		else
			epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev.data.fd, NULL);

	}
}
