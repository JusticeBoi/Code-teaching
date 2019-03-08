#include <timing.h>

double triad(
        double * restrict a,
        double * restrict b,
        double * restrict c,
        int N
        )
{
    double S, E;
    double scalar = 3.0;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = b[i] + scalar * c[i];
    }
    E = getTimeStamp();

    return E-S;
}
