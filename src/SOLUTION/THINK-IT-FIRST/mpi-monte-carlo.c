/**                  _ _              _____ ___
 *  _ __   _____   _(_) | ____      _|___ // _ \
 * | '_ \ / _ \ \ / / | |/ /\ \ /\ / / |_ \ (_) |
 * | | | |  __/\ V /| |   <  \ V  V / ___) \__, |
 * |_| |_|\___| \_/ |_|_|\_\  \_/\_/ |____/  /_/
 **/

#include <assert.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <mpi.h>

#ifdef M_PIl // Intel compiler doesn't define `M_PIl` macro.
#define PI M_PIl
#else
#define PI 3.141592653589793238462643383279502884L
#endif // M_PIl

typedef unsigned long long ull;

int main(int argc, char* argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    double tik = MPI_Wtime();

    srand(time(NULL));

    // Ensure only one additional argument is provided
    if (argc != 2) {
        if (rank == 0) {
            fprintf(stderr, "You can only input one parameter!\n");
        }
        MPI_Finalize();
        return 1;
    }

    const ull n = strtoull(1[argv], NULL, 10);

    ull cnt = 0;
    ull i;
    for (i = rank; i < n; i += size)
    {
        long double x = 1.l * rand() / RAND_MAX, y = 1.l * rand() / RAND_MAX;
        if (x * x + y * y < 1)
            ++cnt;
    }

    ull sum = 0;
    MPI_Reduce(&cnt, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double tok = MPI_Wtime();

    if (!rank) // rank == 0
    {
        long double pi = 4.l * sum / n;
        printf("pi\t= %Lf\nAbs err\t= %Lf\n", pi, fabsl(pi - PI));
        fprintf(stderr, "Wall time: %f\n", tok - tik);
    }

    MPI_Finalize();
    return 0;
}
