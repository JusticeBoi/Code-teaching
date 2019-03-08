#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <allocate.h>
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
    INIT = 0,
    SUM,
    COPY,
    UPDATE,
    TRIAD,
    DAXPY,
    STRIAD,
    SDAXPY,
    NUMBENCH
} benchmark;

extern double init(double*, int);
extern double sum(double*, int);
extern double copy(double*, double*, int);
extern double update(double*, int);
extern double triad(double*, double*, double*, int);
extern double daxpy(double*, double*, int);
extern double striad(double*, double*, double*, double*, int);
extern double sdaxpy(double*, double*, double*, int);

int main (int argc, char** argv)
{
    size_t bytesPerWord = sizeof(double);
    size_t N = 20000000ull;
    double S, E;
    double *a, *b, *c, *d;

    double	avgtime[NUMBENCH],
            maxtime[NUMBENCH],
            mintime[NUMBENCH];

    double times[NUMBENCH][NTIMES];

    double	bytes[NUMBENCH] = {
        1 * sizeof(double) * N,
        1 * sizeof(double) * N,
        2 * sizeof(double) * N,
        2 * sizeof(double) * N,
        3 * sizeof(double) * N,
        3 * sizeof(double) * N,
        4 * sizeof(double) * N,
        4 * sizeof(double) * N
    };

    char	*label[NUMBENCH] = {
        "Init:       ",
        "Sum:        ",
        "Copy:       ",
        "Update:     ",
        "Triad:      ",
        "Daxpy:      ",
        "STriad:     ",
        "SDaxpy:     "};

    a = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    b = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    c = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    d = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);

    for (int i=0; i<NUMBENCH; i++) {
        avgtime[i] = 0;
        maxtime[i] = 0;
        mintime[i] = FLT_MAX;
    }

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
        d[i] = 0.0;
    }

    for ( int k=0; k < NTIMES; k++) {
        times[INIT][k]  = init(a, N);
        times[SUM][k]   = sum(a, N);
        times[COPY][k]  = copy(a, b, N);
        times[UPDATE][k]  = update(a, N);
        times[TRIAD][k] = triad(a, b, c, N);
        times[DAXPY][k] = daxpy(a, b, N);
        times[STRIAD][k] = striad(a, b, c, d, N);
        times[SDAXPY][k] = sdaxpy(a, b, c, N);
    }

    for (int k=1; k<NTIMES; k++) {
        for (int j=0; j<NUMBENCH; j++) {
            avgtime[j] = avgtime[j] + times[j][k];
            mintime[j] = MIN(mintime[j], times[j][k]);
            maxtime[j] = MAX(maxtime[j], times[j][k]);
        }
    }

    printf(HLINE);
    printf("Function      Rate (MB/s)   Avg time     Min time     Max time\n");
    for (int j=0; j<NUMBENCH; j++) {
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
