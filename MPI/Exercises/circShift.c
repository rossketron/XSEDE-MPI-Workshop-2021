#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int this_pe, numToSend, numRecv1, numRecv2;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_pe);

    numToSend = this_pe;
    if (this_pe == 0) {
        MPI_Send(&numToSend, 1, MPI_INT, 7, 10, MPI_COMM_WORLD);
        MPI_Send(&numToSend, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
    } else if (this_pe == 7) {
        MPI_Send(&numToSend, 1, MPI_INT, 6, 10, MPI_COMM_WORLD);
        MPI_Send(&numToSend, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);
    } else {
        MPI_Send(&numToSend, 1, MPI_INT, this_pe + 1, 10, MPI_COMM_WORLD);
        MPI_Send(&numToSend, 1, MPI_INT, this_pe - 1, 10, MPI_COMM_WORLD);
    }

    MPI_Recv(&numRecv1, 1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);
    MPI_Recv(&numRecv2, 1, MPI_INT, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);

    printf("PE %d received from: %d & %d\n", this_pe, numRecv1, numRecv2);

    MPI_Finalize();
    return 0;
}
