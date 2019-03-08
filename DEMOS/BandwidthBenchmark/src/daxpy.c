#include <timing.h>

double daxpy(
        double * restrict a,
        double * restrict b,
        int N
        )
{
    double S, E;
    double scalar = 3.0;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = a[i] + scalar * b[i];
    }
    E = getTimeStamp();

    return E-S;
}
