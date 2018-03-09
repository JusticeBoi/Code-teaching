#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  double wctstart,wctend,cpustart,cpuend;
  int i,SLICES = 100000000;

  double  delta_x,x,sum,Pi;


  delta_x = 1./....;
  
  timing(&wctstart,&cpustart);

  sum = 0.;
  for(i=0; i<SLICES; ++i) {
     x = (i+0.5)*delta_x;
     sum = sum + (sin ( 1.0 + x * x));
  }

  Pi = sum * delta_x;

  timing(&wctend,&cpuend);
  
  printf("Time= %.5lf ,  Pi = %.15lf \n",wctend-wctstart,Pi);

  return 0;
}

