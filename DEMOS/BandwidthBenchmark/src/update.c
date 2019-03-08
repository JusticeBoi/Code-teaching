#include <timing.h>

double update(
        double * restrict a,
        int N
        )
{
    double S, E;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        a[i] = a[i] * 1.3;
    }
    E = getTimeStamp();

    return E-S;
}
