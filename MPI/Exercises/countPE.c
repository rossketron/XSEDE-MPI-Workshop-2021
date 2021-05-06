#include <stdio.h>
#include "mpi.h"

MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN)
{

}

int main(int argc, char **argv)
{
    int this_pe, count;
    int numSend;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_pe);

    numSend = this_pe;
    count = 0;

    if (this_pe == 0) {
        for (count = 1; count < 512; count++) {
            if (MPI_Send(&numSend, 1, MPI_INT, this_pe+1, 10, MPI_COMM_WORLD) != MPI_SUCCESS) {
                break;
            }
        }
    }

    printf("Running on %d PEs\n", count);
    MPI_Finalize();
    return 0;
}
