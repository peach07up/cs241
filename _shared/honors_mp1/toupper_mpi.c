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

#define min(a,b) (a) < (b) ? (a) : (b)

char* map_file(char *filename, int *length_out) 
{
	struct stat file_stat;
	int fd = open(filename, O_RDWR);
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
	void *file = mmap(0, length, PROT_WRITE, MAP_SHARED, fd, 0);
	if (file == (void *)-1) 
	{
		printf("failed to mmap file: %s\n", filename); 
		exit(1);
	}

	*length_out = length;
	return (char *)file;
}

int main(int argc, char *argv[]) 
{
	int rank, size;
	double max_time;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	int length = 0;
	bool print = false;
	if (strncmp(argv[1], "-print", 7) == 0) 
	{
		print = true;
		argv = &argv[1];
	}
	char* file = map_file(argv[1], &length);
	char *upper_file = (char*) calloc(sizeof(char) * length, 1);

	double start = MPI_Wtime();

	// Convert the characters to uppercase here

	double my_time = MPI_Wtime() - start;
	MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	// If we want to print, we need to move all the data to one process
	// Let's move it all to the rank 0 process
	if (print)
	{
		if (rank != 0)
		{
			// I am not rank 0; what should I do?
		}
		if (rank == 0)
		{
			// I am rank 0; what should I do?
		}
	}

	MPI_Finalize();

	if (rank == 0)
	{
		printf("time = %f seconds\n", max_time);  
		if (print)
		{
			printf("%s", upper_file);
		}
	}
}
