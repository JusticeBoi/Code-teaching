#include <timing.h>

double copy(
        double * restrict a,
        double * restrict b,
        int N
        )
{
    double S, E;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = b[i];
    }
    E = getTimeStamp();

    return E-S;
}
