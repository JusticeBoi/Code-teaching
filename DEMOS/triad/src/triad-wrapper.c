#include <x86intrin.h>

#include <timing.h>

extern double triad_asm(int, double*, const double* restrict, const double* restrict, const double* restrict);

double
triad_wrapper(
              double* restrict A,
        const double* restrict B,
        const double* restrict C,
        const double* restrict D,
        int N,
        int iter)
{
    double S, E;

    S = getTimeStamp();
    for(int j = 0; j < iter; j++) {
        triad_asm(N, A, C, D, B);
    }
    E = getTimeStamp();

    return E-S;
}

