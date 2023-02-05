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

#pragma message("GL; HF!")

#ifndef N
#define N 1000000000 // 1e9
#endif               // N

#ifdef M_PIl // Intel compiler doesn't define `M_PIl` macro.
#define PI M_PIl
#else
#define PI 3.141592653589793238462643383279502884L
#endif // M_PIl

typedef unsigned long long ull;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    const ull n = argc > 1 ? strtoull(1 [argv], NULL, 10) : N;

    ull cnt = 0;
    for (ull i = 0; i < n; i++)
    {
        long double x = 1.l * rand() / RAND_MAX, y = 1.l * rand() / RAND_MAX;
        if (x * x + y * y < 1)
            ++cnt;
    }

    ull sum = cnt;
    long double pi = 4.l * sum / n;
    printf("pi\t= %Lf\nAbs err\t= %Lf\n", pi, fabsl(pi - PI));
    return 0;
}
