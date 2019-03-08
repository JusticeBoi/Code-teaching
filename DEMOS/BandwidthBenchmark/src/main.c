#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
# include <limits.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <timing.h>

#define ARRAY_ALIGNMENT	64
#define NTIMES	10

# define HLINE "-------------------------------------------------------------\n"

#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif

typedef enum benchmark {
    COPY = 0,
    TRIAD,
    NUMBENCH
} benchmark;



int main (int argc, char** argv)
{
    size_t bytesPerWord;
    size_t N = 20000000ull;
    double S, E;
    double *a, *b, *c, *d;
    double scalar;
    double	avgtime[NUMBENCH] = {0},
            maxtime[NUMBENCH] = {0},
            mintime[NUMBENCH];

    bytesPerWord = sizeof(double);

    a = (double*) aligned_alloc( ARRAY_ALIGNMENT, N * bytesPerWord);
    b = (double*) aligned_alloc( ARRAY_ALIGNMENT, N * bytesPerWord);
    c = (double*) aligned_alloc( ARRAY_ALIGNMENT, N * bytesPerWord);
    d = (double*) aligned_alloc( ARRAY_ALIGNMENT, N * bytesPerWord);

#ifdef _OPENMP
    printf(HLINE);
#pragma omp parallel private(k)
    {
        k = omp_get_num_threads();
        printf ("Number of Threads requested = %i\n",k);
    }
#endif

    for (int i=0; i<N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
        c[i] = 0.0;
    }

    /* S = getTimeStamp(); */
/* #pragma omp parallel for */
    /* for (int i=0; i<N; i++) { */
    /*     a[j] = 2.0E0 * a[j]; */
    /* } */
    /* E = getTimeStamp(); */

    printf(HLINE);

    for ( int k=0; k < NTIMES; k++) {

        times[COPY][k] = copy(a, b, N);
        times[TRIAD][k] = triad(a, b, c, N);
    }

    for (k=1; k<NTIMES; k++) {
        for (j=0; j<NUMBENCH; j++) {
            avgtime[j] = avgtime[j] + times[j][k];
            mintime[j] = MIN(mintime[j], times[j][k]);
            maxtime[j] = MAX(maxtime[j], times[j][k]);
        }
    }

    printf(HLINE);
    printf("Function      Rate (MB/s)   Avg time     Min time     Max time\n");
    for (j=0; j<NUMBENCH; j++) {
        avgtime[j] = avgtime[j]/(double)(NTIMES-1);

        printf("%s%11.4f  %11.4f  %11.4f  %11.4f\n", label[j],
                1.0E-06 * bytes[j]/mintime[j],
                avgtime[j],
                mintime[j],
                maxtime[j]);
    }
    printf(HLINE);

    return EXIT_SUCCESS;
}
