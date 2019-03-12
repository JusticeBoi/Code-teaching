#include <x86intrin.h>

#include <timing.h>


double
triad_intrinsics(
              double* restrict A,
        const double* restrict B,
        const double* restrict C,
        const double* restrict D,
        int N,
        int iter)
{
    double S, E;
    __m256d srcB;
    __m256d srcC;
    __m256d srcD;
    __m256d dst;

    S = getTimeStamp();
    for(int j = 0; j < iter; j++) {
        for(int i = 0; i < N; i+= 4) {
            srcB = _mm256_loadu_pd(B+i);
            srcC = _mm256_loadu_pd(C+i);
            srcD = _mm256_loadu_pd(D+i);
            dst = _mm256_fmadd_pd(srcD, srcC, srcB);
            _mm256_store_pd(A+i, dst);
        }
    }
    E = getTimeStamp();

    return E-S;
}

