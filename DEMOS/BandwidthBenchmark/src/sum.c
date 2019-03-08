#include <timing.h>

double sum(
        double * restrict a,
        int N
        )
{
    double S, E;
    double sum = 0.0;

    S = getTimeStamp();
#pragma omp parallel for
    for (int i=0; i<N; i++) {
        sum += a[i];
    }
    E = getTimeStamp();

    a[10] = sum;

    return E-S;
}
