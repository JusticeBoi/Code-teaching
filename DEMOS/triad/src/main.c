#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

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

extern double triad(double*, double*, double*, double*, int, int);
extern double triad_intrinsics(double*, double*, double*, double*, int, int);
extern double triad_asm(double*, double*, double*, double*, int, int);

int main (int argc, char** argv)
{
    size_t bytesPerWord = sizeof(double);
    size_t N = 20000000ull;
    int iter = 10;
    double *a, *b, *c, *d;
    double	avgtime = 0.0, maxtime = 0.0, mintime = FLT_MAX;
    double times[NTIMES];

    if ( argc > 2 ) {
        N = atoi(argv[1]);
        iter = atoi(argv[2]);
    } else {
        printf("Usage: %s <N> <ITER>\n",argv[0]);
        exit(EXIT_SUCCESS);
    }

    a = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    b = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    c = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);
    d = (double*) allocate( ARRAY_ALIGNMENT, N * bytesPerWord);

    for (int i=0; i<N; i++) {
        a[i] = 1.0;
        b[i] = 2.0;
        c[i] = 3.0;
        d[i] = 4.0;
    }

    for ( int k=0; k < NTIMES; k++) {
        times[k]  = triad(a, b, c, d, N, iter);
    }

    for (int k=1; k<NTIMES; k++) {
            avgtime = avgtime + times[k];
            mintime = MIN(mintime, times[k]);
            maxtime = MAX(maxtime, times[k]);
    }


    printf(HLINE);
    printf("Time: %f sec\n", mintime);
    printf("Working set: %.2f kB\n", 4.0 * N * bytesPerWord / 1000.0);
    printf(" %.2f MB/s\n",1.0E-06 * (double) iter * (double) N*32.0/mintime);
    printf(" %.2f MFLops/s\n",1.0E-06 * (double) iter * (double) N*2.0/mintime);
    printf(HLINE);

    return EXIT_SUCCESS;
}
