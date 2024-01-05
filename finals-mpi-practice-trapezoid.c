#include <stdio.h>
#include <mpi.h>
#include <string.h>

double Trap(double left, double right, double count, double base_len) {
    double estimate, x;
    
    for(int i = 1; i < count; ++i) {
        x = left + i*base_len;
        estimate += f(x);
    }
}



// SIMD (Single Program Multiple Data)
int main(void)
{
    int p;
    int my_rank;

    int n = 1024; // number of trapezoids
    int local_n;

    double a = 0.0, b = 3.0, h, local_a, local_b;
    double local_int, total_int;
    int source;

    // Defines a Communicator MPI_COMM_WORLD
    MPI_Init(NULL, NULL);

    // Communicators
    MPI_Comm_size(MPI_COMM_WORLD, &p);       // number of processes in the communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // calling process' rank

    h = (b - a) / n;
    local_n = n / p;
    local_a = a + my_rank*local_n*h;
    local_int = Trap(local_a, local_b, local_n, h);

    if (my_rank != 0)
    {
        MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        total_int = local_int;

        for (int source = 1; source < p; ++source)
        {
            MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int += local_int;
        }

        printf("With n = %d trapezoids, our estimate from %f to %f is: ", n, a, b, total_int);
    }

    MPI_Finalize();

    printf("Sorry\n");

    return 0;
}