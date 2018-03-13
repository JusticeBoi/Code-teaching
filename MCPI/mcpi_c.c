#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timing.h"

int main() {
  double wcstart,wcend,ct,x,y,pi;
  unsigned int seed = 123;
  int i,count=0,nn=342000000;
  
  timing(&wcstart, &ct);

  seed = 2;

  for(i=0; i<nn; ++i) {
    x = rand_r(&seed)/(double)RAND_MAX;
    y = rand_r(&seed)/(double)RAND_MAX;
    if(sqrt(x*x+y*y) <1.0) ++count;
  }  


  pi = 4.0*(double)count/nn; 

  timing(&wcend, &ct);
 
  printf("Time: %.3lf sec, accuracy: %.12lf\n",wcend-wcstart,fabs(M_PI-pi)/M_PI);

  return 0;
}

  
