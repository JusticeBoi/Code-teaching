#include "PDE.h"
#include <math.h>
#include <iostream>
#include <omp.h>

//default boundary function as in ex01
double defaultBoundary(int i, int j, double h_x, double h_y)
{
    return sin(M_PI*i*h_x)*sinh(M_PI*j*h_y);
}
//default rhs function as in ex01
double zeroFunc(int i, int j, double h_x, double h_y)
{
    return 0 + 0*i*h_x + 0*j*h_y;
}

//Constructor
PDE::PDE(int len_x_, int len_y_, int grids_x_, int grids_y_):len_x(len_x_), len_y(len_y_), grids_x(grids_x_+2*HALO), grids_y(grids_y_+2*HALO)
{
    h_x = static_cast<double>(len_x)/(grids_x-1.0);
    h_y = static_cast<double>(len_y)/(grids_y-1.0);

    initFunc = zeroFunc;

    //by default all boundary is Dirichlet
    for (int i=0; i<4; ++i)
        boundary[i] = Dirichlet;

    for (int i=0; i<4; ++i)
        boundaryFunc[i] = zeroFunc;
}

int PDE::numGrids_x(bool halo)
{
    int halo_x = halo ? 0:2*HALO;
    return (grids_x-halo_x);
}

int PDE::numGrids_y(bool halo)
{
    int halo_y = halo ? 0:2*HALO;
    return (grids_y-halo_y);
}


void PDE::init(Grid *grid)
{
#if DEBUG
    assert((grid->numGrids_y(true)==grids_y) && (grid->numGrids_x(true)==grids_x));
#endif
    grid->fill(std::bind(initFunc,std::placeholders::_1,std::placeholders::_2,h_x,h_y));
}

// Boundary Condition
void PDE::applyBoundary(Grid *u)
{
#if DEBUG
    assert((u->numGrids_y(true)==grids_y) && (u->numGrids_x(true)==grids_x));
#endif
    if(boundary[NORTH]==Dirichlet){
        u->fillBoundary(std::bind(boundaryFunc[NORTH],std::placeholders::_1,std::placeholders::_2,h_x,h_y),NORTH);
    }
    if(boundary[SOUTH]==Dirichlet){
        u->fillBoundary(std::bind(boundaryFunc[SOUTH],std::placeholders::_1,std::placeholders::_2,h_x,h_y),SOUTH);
    }
    if(boundary[EAST]==Dirichlet){
        u->fillBoundary(std::bind(boundaryFunc[EAST],std::placeholders::_1,std::placeholders::_2,h_x,h_y),EAST);
    }
    if(boundary[WEST]==Dirichlet){
        u->fillBoundary(std::bind(boundaryFunc[WEST],std::placeholders::_1,std::placeholders::_2,h_x,h_y),WEST);
    }
}

//It refreshes Neumann boundary, 2 nd argument is to allow for refreshing with 0 shifts, ie in coarser levels
void PDE::refreshBoundary(Grid *u)
{
#if DEBUG
    assert((u->numGrids_y(true)==grids_y) && (u->numGrids_x(true)==grids_x));
#endif
    if(boundary[NORTH]==Neumann){
        u->copyToHalo(std::bind(boundaryFunc[NORTH],std::placeholders::_1,std::placeholders::_2,h_x,h_y),NORTH);
    }
    if(boundary[SOUTH]==Neumann){
        u->copyToHalo(std::bind(boundaryFunc[SOUTH],std::placeholders::_1,std::placeholders::_2,h_x,h_y),SOUTH);
    }
    if(boundary[EAST]==Neumann){
        u->copyToHalo(std::bind(boundaryFunc[EAST],std::placeholders::_1,std::placeholders::_2,h_x,h_y),EAST);
    }
    if(boundary[WEST]==Neumann){
        u->copyToHalo(std::bind(boundaryFunc[WEST],std::placeholders::_1,std::placeholders::_2,h_x,h_y),WEST);
    }
}


//Applies stencil operation on to u
//i.e., res = A*u
void PDE::applyStencil(Grid* res, Grid* u)
{
    START_TIMER(APPLY_STENCIL);

#if DEBUG
    assert((res->numGrids_y(true)==grids_y) && (res->numGrids_x(true)==grids_x));
    assert((u->numGrids_y(true)==grids_y) && (u->numGrids_x(true)==grids_x));
#endif
    const int xSize = numGrids_x(true);
    const int ySize = numGrids_y(true);

    const double w_x = 1.0/(h_x*h_x);
    const double w_y = 1.0/(h_y*h_y);
    const double w_c = 2.0*w_x + 2.0*w_y;

#pragma omp parallel for
    for ( int j=1; j<ySize-1; ++j)
    {
#pragma omp simd
        for ( int i=1; i<xSize-1; ++i)
        {
            (*res)(j,i) = w_c*(*u)(j,i) - w_y*((*u)(j+1,i) + (*u)(j-1,i)) - w_x*((*u)(j,i+1) + (*u)(j,i-1));
        }
    }

    STOP_TIMER(APPLY_STENCIL);
}

/*
!$OMP parallel private(nthreads,istart,iend,tid,kk,it,k,i)
  nthreads = omp_get_num_threads()
  tid = omp_get_thread_num()
  istart= (imax-1)/nthreads * tid +1
  iend  = istart+(imax-1)/nthreads-1
  do it=1,itmax
     do k=1,kmax-1+nthreads-1
        kk = k - tid
        if(kk .ge. 1 .and. kk .le. kmax-1) then
           do i=istart, iend
              ! may also use pipeline-optimized version
              phi(i,kk) = 0.25d0 * ( phi(i,kk-1)+phi(i+1,kk) +  phi(i,kk+1) + phi(i-1,kk))
           enddo
        endif
!$OMP barrier
     enddo ! k
  enddo !it
!$OMP end parallel
*/     

void PDE::GSPreCon(Grid* rhs, Grid *u)
{
    START_TIMER(GS_PRE_CON);

#if DEBUG
    assert((rhs->numGrids_y(true)==grids_y) && (rhs->numGrids_x(true)==grids_x));
    assert((u->numGrids_y(true)==grids_y) && (u->numGrids_x(true)==grids_x));
#endif
    const int xSize = u->numGrids_x(true);
    const int ySize = u->numGrids_y(true);


    const double w_x = 1.0/(h_x*h_x);
    const double w_y = 1.0/(h_y*h_y);
    const double w_c = 1.0/static_cast<double>((2.0*w_x + 2.0*w_y));

    //    int nthreads,tid,istart,iend;
    
    //forward substitution
#pragma omp parallel
  {
    int nthreads = omp_get_num_threads();
    int tid = omp_get_thread_num();
    int istart = (xSize-2)/nthreads*tid+1;
    int iend = istart+(xSize-2)/nthreads;
    if(tid == nthreads-1)
      iend = xSize-2;
    for ( int j=1; j<ySize-1+nthreads-1; ++j)
    {
      int jj = j-tid;
      if(jj>0 && jj < ySize-1) {
        for ( int i=istart; i<iend; ++i)
        {
            (*u)(jj,i) = w_c*((*rhs)(jj,i) + (w_y*(*u)(jj-1,i) + w_x*(*u)(jj,i-1)));
        }
      }
#pragma omp barrier
    }
    //backward substitution
    // std::cerr << "backsub" << std::endl;
    for ( int j=ySize-2+nthreads-1; j>0; --j)
    {
      int jj = j-tid;
      if(jj>0 && jj < ySize-1) {
	//	std::cerr << "Thread " << tid << ": from " << iend-1 << " to " << istart << " at jj = " << jj << std::endl;
        for ( int i=iend-1; i>=istart; --i)
        {
            (*u)(jj,i) = (*u)(jj,i) + w_c*(w_y*(*u)(jj+1,i) + w_x*(*u)(jj,i+1));
        }
      }
#pragma omp barrier
    }
  }

    STOP_TIMER(GS_PRE_CON);
}

int PDE::solve(Grid *x, Grid *b, Solver type, int niter, double tol)
{
    SolverClass solver(this, x, b);
    if(type==CG)
    {
        return solver.CG(niter, tol);
    }
    else if(type==PCG)
    {
        return solver.PCG(niter, tol);
    }
    else
    {
        printf("Solver not existing\n");
        return -1;
    }
}
