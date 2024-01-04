#include <stdio.h>
#include <mpi.h>
#include <string.h>

const int max_string = 100;

int main(void)
{
    char greeting[max_string];
    int p;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0)
    {
        sprintf(greeting, "Greetings from process %d of %d\n", my_rank, p);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        printf("Greetings from process %d of %d!\n", my_rank, p);

        for (int q = 1; q < p; ++q)
        {
            MPI_Recv(greeting, max_string, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("%s\n", greeting);
    }

    MPI_Finalize();

    printf("Sorry\n");

    return 0;
}