// skeleton
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

int main(int argc, char** argv) {

  double wct_start,wct_end,cput_start,cput_end;
  int id,nt,k;
  int NITER;
  double t = 0;

  NITER=1;
  do {
    // time measurement
    timing(&wct_start, &cput_start);

    for(k=0; k<NITER; ++k) {
      // PUT YOUR CODE HERE
    }
    timing(&wct_end, &cput_end);
    NITER = NITER*2;
  } while (wct_end-wct_start<0.2);

  NITER = NITER/2;

  printf("Total walltime: %f\n",wct_end-wct_start);
  
  return 0;
}
