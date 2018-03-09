#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

int main() {
  unsigned int seed = 123;
  long hist[16],j;
  int i;
  double wcstart,wcend,ct;

  for(i=0; i<16; ++i)
    hist[i]=0;
  timing(&wcstart, &ct);
  for(j=0; j<1000000000; ++j) {
    hist[rand_r(&seed) & 0xf]++;
  }
  timing(&wcend, &ct);
  for(i=0; i<16; ++i) {
    printf("hist[%d]=%ld\n",i,hist[i]);
  }
  printf("Time: %lf sec\n",wcend-wcstart);
  
  return 0;
}

