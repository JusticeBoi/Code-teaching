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
#ifndef ABS
#define ABS(a) ((a) >= 0 ? (a) : -(a))
#endif

extern double triad(double*, double*, double*, double*, int, int);
extern double triad_intrinsics(double*, double*, double*, double*, int, int);
extern double triad_wrapper(double*, double*, double*, double*, int, int);

extern void check(double*, double*, double*, double*, int, int);

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
        /* times[k]  = triad(a, b, c, d, N, iter); */
        /* times[k]  = triad_intrinsics(a, b, c, d, N, iter); */
        times[k]  = triad_wrapper(a, b, c, d, N, iter);
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

    check(a, b, c, d, N, NTIMES * iter);

    return EXIT_SUCCESS;
}

void check(
        double * a,
        double * b,
        double * c,
        double * d,
        int N, int ITER
        )
{
    double aj, bj, cj, dj;
    double asum, bsum, csum, dsum;
    double epsilon;

    /* reproduce initialization */
    aj = 1.0;
    bj = 2.0;
    cj = 3.0;
    dj = 4.0;

    /* now execute timing loop */
    for (int k=0; k<ITER; k++) {
        aj = bj + cj * dj;
    }

    aj = aj * (double) (N);
    bj = bj * (double) (N);
    cj = cj * (double) (N);
    dj = dj * (double) (N);

    asum = 0.0; bsum = 0.0; csum = 0.0; dsum = 0.0;

    for (int i=0; i<N; i++) {
        asum += a[i];
        bsum += b[i];
        csum += c[i];
        dsum += d[i];

    }

#ifdef VERBOSE
    printf ("Results Comparison: \n");
    printf ("        Expected  : %f %f %f \n",aj,bj,cj);
    printf ("        Observed  : %f %f %f \n",asum,bsum,csum);
#endif

    epsilon = 1.e-8;

    if (ABS(aj-asum)/asum > epsilon) {
        printf ("Failed Validation on array a[]\n");
        printf ("        Expected  : %f \n",aj);
        printf ("        Observed  : %f \n",asum);

    }
    else if (ABS(bj-bsum)/bsum > epsilon) {
        printf ("Failed Validation on array b[]\n");
        printf ("        Expected  : %f \n",bj);
        printf ("        Observed  : %f \n",bsum);

    }
    else if (ABS(cj-csum)/csum > epsilon) {
        printf ("Failed Validation on array c[]\n");
        printf ("        Expected  : %f \n",cj);
        printf ("        Observed  : %f \n",csum);

    }
    else if (ABS(dj-dsum)/dsum > epsilon) {
        printf ("Failed Validation on array d[]\n");
        printf ("        Expected  : %f \n",dj);
        printf ("        Observed  : %f \n",dsum);

    }
    else {
        printf ("Solution Validates\n");

    }
}
