#include <stdlib.h>
#include <time.h>

double mysecond()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1.e-9;
}

double mysecond_()
{
    return mysecond();
}

