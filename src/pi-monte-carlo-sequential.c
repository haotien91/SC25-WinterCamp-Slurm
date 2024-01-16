#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef N
#define N 1000000000 // 1e9
#endif

#ifdef M_PIl
#define PI M_PIl
#else
#define PI 3.141592653589793238462643383279502884L
#endif

int main(int argc, char* argv[])
{
    // Ensure only one additional argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_tosses>\n", argv[0]);
        return 1;
    }

    clock_t tik = clock();
    srand(time(NULL)); // Seed random number generator

    const long long int n = strtoull(argv[1], NULL, 10);
    long long int number_in_circle = 0;
    long long int toss;

    for (toss = 0; toss < n; ++toss) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        double distance_squared = x * x + y * y;
        if (distance_squared <= 1) {
            number_in_circle++;
        }
    }

    double pi_estimate = 4 * (double)number_in_circle / n;
    printf("pi_estimate\t= %.15Lf\nAbs err\t= %.15Lf\n", pi_estimate, fabsl(pi_estimate - PI));
    
    clock_t tok = clock();
    double time_spent = (double)(tok - tik) / CLOCKS_PER_SEC;
    fprintf(stderr, "Wall time: %f seconds\n", time_spent);

    return 0;
}

