#include <timing.h>

double sdaxpy(
        double * restrict a,
        double * restrict b,
        double * restrict c,
        int N
        )
{
    double S, E;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = a[i] + b[i] * c[i];
    }
    E = getTimeStamp();

    return E-S;
}
