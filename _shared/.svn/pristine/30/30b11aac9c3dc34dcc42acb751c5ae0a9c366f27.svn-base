CC = icpc
OMPFLAG = -openmp
MPICC = mpicxx

all : toupper_serial toupper_omp toupper_mpi histogram_serial histogram_omp histogram_mpi eight_shakespeares.txt

histogram_serial : histogram_serial.c
	$(CC) -I/opt/intel/tbb/2.2/include -L/opt/intel/tbb/2.2/lib/intel64 -o $@ $? -ltbb 

histogram_omp : histogram_omp.c
	$(CC) $(OMPFLAG) -I/opt/intel/tbb/2.2/include -L/opt/intel/tbb/2.2/lib/intel64 -o $@ $? -ltbb 

histogram_mpi : histogram_mpi.c
	$(MPICC) -o $@ $?

toupper_serial : toupper_serial.c
	$(CC) -I/opt/intel/tbb/2.2/include -L/opt/intel/tbb/2.2/lib/intel64 -o $@ $? -ltbb 

toupper_omp : toupper_omp.c
	$(CC) $(OMPFLAG) -I/opt/intel/tbb/2.2/include -L/opt/intel/tbb/2.2/lib/intel64 -o $@ $? -ltbb 

toupper_mpi : toupper_mpi.c
	$(MPICC) -o $@ $?

shakespeare.txt :
	wget http://ocw.mit.edu/ans7870/6/6.006/s08/lecturenotes/files/t8.shakespeare.txt -O shakespeare.txt

eight_shakespeares.txt : shakespeare.txt
	touch eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt
	cat shakespeare.txt >> eight_shakespeares.txt

clean : 
	-rm histogram_serial
	-rm histogram_omp
	-rm histogram_mpi
	-rm toupper_serial
	-rm toupper_omp
	-rm toupper_mpi
