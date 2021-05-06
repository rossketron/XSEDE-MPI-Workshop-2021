#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int n, this_pe, nProcs;
    float mypi, pi, h, x, start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &this_pe);

    if (this_pe == 0) {
        printf("How many intervals? ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    mypi = 0;
    h = (float) 2/n;  /* size of each slice of circle */
    start = (this_pe * 2 / nProcs) - 1;
    end = ((this_pe + 1) * 2 / nProcs) - 1;

    for (x = start; x < end; x = x + h) {
        mypi = mypi + h * 2 * sqrt(1-x*x);    
    }

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (this_pe == 0) {
        printf("Pi is approximately %lf\n", pi);
        printf("Error is %lf\n", pi-3.14159265358979323846);
    }

    MPI_Finalize();
    return 0;
}
