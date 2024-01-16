#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#ifdef M_PIl
#define PI M_PIl
#else
#define PI 3.141592653589793238462643383279502884L
#endif

typedef unsigned long long ull;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "You can only input one parameter!\n");
        return 1;
    } 
    
    const ull n = strtoull(argv[1], NULL, 10);
    long double sum = 0.0;
    long double step = 1.0 / n;

    for (ull i = 0; i < n; ++i) {
        long double x = (i + 0.5) * step; // Midpoint of each subinterval
        sum += 4.0 / (1.0 + x * x);
    }

    long double pi = sum * step;
    printf("pi\t= %.15Lf\nAbs err\t= %.15Lf\n", pi, fabsl(pi - PI));
    return 0;
}

