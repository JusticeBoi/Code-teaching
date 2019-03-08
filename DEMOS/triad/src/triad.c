#include <stdio.h>

#include <timing.h>

double
triad(
              double* restrict A,
        const double* restrict B,
        const double* restrict C,
        const double* restrict D,
        int N,
        int iter)
{
    double S, E;

    S = getTimeStamp();
    for(int j = 0; j < iter; j++)
    {
        for(int i = 0; i < N; i++)
        {
            A[i] = B[i] + D[i] * C[i];
        }

        if (A[N-1] > 20) printf("Ai = %f\n",A[N-1]);
    }
    E = getTimeStamp();

    return E-S;
}

