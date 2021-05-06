#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int PE_num, numToSend, numToReceive;
    MPI_Status status;

    numToSend = 42;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &PE_num);

    if (PE_num == 0) {
        MPI_Recv(&numToReceive, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("Number received is: %d\n", numToReceive);
    } else {
        MPI_Send(&numToSend, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);    
    }

    MPI_Finalize();
    return 0;
}
