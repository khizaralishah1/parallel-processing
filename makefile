all:
	mpicc -g -Wall -o mpiprog finals-mpi-practice.c
	mpiexec -oversubscribe -np 3 ./mpiprog

tzoid:
	mpicc -g -Wall -o mpiprog finals-mpi-practice-trapezoid.c
	mpiexec -oversubscribe -np 4 ./mpiprog