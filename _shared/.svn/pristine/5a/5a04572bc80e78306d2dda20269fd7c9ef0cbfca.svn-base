#include <string.h>	
#include "mpi.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NOTICK

#ifndef NOTICK
#include "tbb/tick_count.h"
using tbb::tick_count;
#endif 

int min(int a, int b) { return (a) < (b) ? (a) : (b); }

char* map_file(char *filename, int *length_out) 
{
	struct stat file_stat;
	int fd = open(filename, O_RDONLY);
	if (fd == -1) 
	{
		printf("failed to open file: %s\n", filename); 
		exit(1);
	}
	if (fstat(fd, &file_stat) != 0) 
	{
		printf("failed to stat file: %s\n", filename); 
		exit(1);
	}
	off_t length = file_stat.st_size;
	void *file = mmap(0, length, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (file == (void *)-1) 
	{
		printf("failed to stat file: %s\n", filename); 
		exit(1);
	}

	*length_out = length;
	return (char *)file;
}

int main(int argc, char *argv[]) 
{
	int rank, size;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	int length = 0;
	bool print = false;
	if (strncmp(argv[1], "-print", 7) == 0) {
		print = true;
		argv = &argv[1];
	}
	double max_time;
	char *file = map_file(argv[1], &length);
	unsigned histogram[256] = {0};

	double start = MPI_Wtime();


	// Your code here! (and maybe elsewhere)


	double time = MPI_Wtime() - start;
	MPI_Reduce(&time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	MPI_Finalize();

	if (rank == 0)
		printf("time = %f seconds\n", max_time);  

	if (print && (rank == 0)) {
		for (int i = 0 ; i < 256 ; i ++) {
			if (histogram[i] != 0) {
				printf("%c (%d): %d\n", i, i, histogram[i]);
			}
		}
	}
}
