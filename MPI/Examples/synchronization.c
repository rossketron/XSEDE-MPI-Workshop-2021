#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int this_PE, numRecv, numSend, result;
    int i;
    MPI_Status status;

    numSend = 4;
    result = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_PE);

    if (this_PE == 0) {
        for (i = 1; i < 4; i++) {
            MPI_Send(&numSend, 1, MPI_INT, i, 10, MPI_COMM_WORLD);    
        }
    } else {
        MPI_Recv(&numRecv, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
        result = numRecv * this_PE;
    }

    for (i = 1; i < 4; i++) {
        MPI_Barrier(MPI_COMM_WORLD);
        if (i == this_PE) {
            printf("PE %d's result is %d.\n", this_PE, result);    
        }
    }

    if (this_PE == 0) {
        for (i = 1; i < 4; i++) {
            MPI_Recv(&numRecv, 1, MPI_INT, i, 10, MPI_COMM_WORLD, &status);
            result += numRecv;
        }
        printf("Total is %d.\n", result);
    } else {
        MPI_Send(&result, 1, MPI_INT, 0, 10, MPI_COMM_WORLD);    
    }

    MPI_Finalize();
    return 0;
}
