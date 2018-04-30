!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! triad.f90 benchmark demo code
! G. Hager, 2010
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
program triad
!!  use likwid
  implicit none

  double precision, dimension(:),allocatable :: X,Y
  double precision, dimension(:,:),allocatable :: A
! Intel-specific: 16-byte alignment of allocatables
!DEC$ ATTRIBUTES ALIGN: 32 :: A
!DEC$ ATTRIBUTES ALIGN: 32 :: Y
!DEC$ ATTRIBUTES ALIGN: 32 :: X
  double precision :: MFLOPS,WT
  integer :: N,SIZE,i,j,NC
  integer :: R,ovl_rep

!!  call likwid_markerInit()

!$OMP PARALLEL
  ! Each thread must add itself to the Marker API, therefore must be
  ! in parallel region.
!!  call likwid_markerthreadInit()
  ! Optional. Register region name and initialize hash table entries.
!!  call likwid_markerRegisterRegion("dMVM")
!$OMP END PARALLEL

  ! SIZE is number of elements, N is number of rows
  read *,N,SIZE
  NC = dble(SIZE)/N

  allocate(X(1:NC),Y(1:N),A(1:N,1:NC))

!$OMP parallel do
  do i=1,NC
     X(i) = 3.d0
     do j=1,N
        if(i.eq.1) Y(j) = 2.d0 
        A(j,i)=dble(i)*j/SIZE
     enddo
  enddo
!$OMP end parallel do

  R = 1

  ! warm up
  call do_it(A,X,Y,N,NC,R,WT)
  ovl_rep = 1

  do
     call do_it(A,X,Y,N,NC,R,WT)
     ovl_rep = ovl_rep + R
     ! exit if duration was above some limit
     if(WT.ge.1.0d0) exit
     ! else do it again with doubled repeat count
     R = R*2
  enddo

  MFLOPS = 2.d0*R*dble(N)*NC/(WT*1.d6) ! compute MFlop/sec rate
  print 111,"Iter: ",ovl_rep, " Length: ",N,NC," MFLOP/s: ",MFLOPS
111 format(a,i6,a,i6,i7,a,f5.0)
  deallocate(A,X,Y)
!!  call likwid_markerClose()
end program triad

subroutine do_it(A,X,Y,N,NC,REP,WT)
  implicit none
  integer, intent(in) :: N,NC
  integer(kind=8), intent(in) :: REP
  double precision, dimension(N,NC), intent(in) :: A
  double precision, dimension(NC), intent(in) :: X
  double precision, dimension(N), intent(out) :: Y
  double precision, intent(out) :: WT
  double precision :: S,E
  integer :: N2
  integer :: j,c,r

  N2 = N/2

  call get_walltime(S)
 
!$OMP PARALLEL PRIVATE(j)
!!  call likwid_markerStartRegion("dMVM")
     do j=1,REP
! Intel-specific: Assume aligned moves
!$OMP DO REDUCTION(+:Y)
        do c=1,NC
!DIR$ vector aligned
!DIR$ vector temporal
          do r=1,N
            Y(r) = Y(r) + A(r,c) * X(c)
          enddo
        enddo
!$OMP END DO        ! prevent loop interchange
        if(Y(N2).lt.-1.d99) then
          call dummy(X,Y)
          stop
        endif
     enddo
!!  call likwid_markerStopRegion("dMVM")
!  call likwid_markerNextGroup()
!$OMP END PARALLEL
  
  call get_walltime(E)
  
  WT = E-S

end subroutine do_it

