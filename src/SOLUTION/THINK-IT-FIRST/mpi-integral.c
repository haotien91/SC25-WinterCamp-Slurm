#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#ifdef M_PIl
#define PI M_PIl
#else
#define PI 3.141592653589793238462643383279502884L
#endif

typedef unsigned long long ull;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Ensure only one additional argument is provided
    if (argc != 2) {
        if (rank == 0) {
            fprintf(stderr, "You can only input one parameter!\n");
        }
        MPI_Finalize();
        return 1;
    }

    const ull n = strtoull(argv[1], NULL, 10);
    long double sum = 0.0;
    long double step = 1.0 / n;

    ull chunk_size = n / size;
    ull start = rank * chunk_size;
    ull end = (rank == size - 1) ? n : start + chunk_size;

    ull i;
    for (i = start; i < end; ++i) {
        long double x = (i + 0.5) * step; // Midpoint of each subinterval
        sum += 4.0 / (1.0 + x * x);
    }

    long double global_sum;
    MPI_Reduce(&sum, &global_sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        long double pi = global_sum * step;
        printf("pi\t= %.15Lf\nAbs err\t= %.15Lf\n", pi, fabsl(pi - PI));
    }

    MPI_Finalize();
    return 0;
}

