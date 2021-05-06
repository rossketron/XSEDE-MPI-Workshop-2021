#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int PE_num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &PE_num);

    printf("Hello from %d\n", PE_num);

    MPI_Finalize();
    return 0;
}
