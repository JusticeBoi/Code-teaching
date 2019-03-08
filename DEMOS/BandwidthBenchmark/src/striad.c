#include <timing.h>

double striad(
        double * restrict a,
        double * restrict b,
        double * restrict c,
        double * restrict d,
        int N
        )
{
    double S, E;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = b[i] + d[i] * c[i];
    }
    E = getTimeStamp();

    return E-S;
}
