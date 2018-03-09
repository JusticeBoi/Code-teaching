#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "timing.h"

#define MAT(i,j) mat[(i)*N+(j)]
#define S(i,j) s[(i)*N+(j)]

void dummy(double*);

int main(int argc, char** argv) {
  int N;
  double *mat, *s, val, vv;
  int i, j,R,iter,*v;
  double wct_start,wct_end,cput_start,cput_end,runtime;

  if(argc!=2) {
    fprintf(stderr, "Usage: %s <size>\n",argv[0]);
    exit(1);
  }

  N = atoi(argv[1]);
  mat = (double*)malloc(N*N*sizeof(double));
  s = (double*)malloc(N*N*sizeof(double));
  v = (int*)malloc(N*sizeof(int));

  for(i=0; i<N ; ++i) {
    v[i] = rand();
    for(j=0; j<N; ++j)
      MAT(i,j) = S(i,j) = rand()/RAND_MAX;
  }

  R=1;

  do {
    timing(&wct_start, &cput_start);

    for(iter=0; iter<R; ++iter) {
      
      for(i=0; i<N ; ++i) {
	    for(j=0; j<N; ++j) {
	      val = (double)(v[i] % 256);
	      MAT(j,i) = S(j,i)*(sin(val)*sin(val)-cos(val)*cos(val));
	    }
      }
      if(MAT(2,2)<-1000.) dummy(&MAT(2,2));
    }
    
    timing(&wct_end, &cput_end);
    runtime = wct_end-wct_start;
    R += R;
  } while(runtime<0.2);
  
  R=R/2;
    
  printf("Performance: %lf MIt/s\n",(double)R*N*N/runtime/1000000.);

  
  return 0;
}
