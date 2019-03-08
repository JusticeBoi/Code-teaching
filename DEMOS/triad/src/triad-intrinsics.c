#include <stdio.h>
#include <x86intrin.h>

#include <timing.h>


double
triad_intrinsics(
              double* restrict A,
        const double* restrict B,
        const double* restrict C,
        const double* restrict D,
        int iter,
        int N)
{
    double S, E;
    __m256d srcB;
    __m256d srcC;
    __m256d srcD;
    __m256d dst;

    S = getTimeStamp();
    for(int j = 0; j < iter; j++) {
        for(int i = 0; i < N; i+= 4) {
            srcB = __mm256_loadu_pd(B+i);
            srcC = __mm256_loadu_pd(C+i);
            srcD = __mm256_loadu_pd(D+i);
            dst = __mm256_fmadd_pd(srcB, srcC, srcD);
            __mm256_store_pd(D+i, dst);
        }
    }
    E = getTimeStamp();

    return E-S;
}

