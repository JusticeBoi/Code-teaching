subroutine jacobi_line(d,s,top,bottom,front,back,n)
    implicit none
    integer :: n
    double precision, dimension(*) :: d,s,top,bottom,front,back
    integer :: i,start
    double precision, parameter :: oos=1.d0/6.d0

    do i=2,n-1
       d(i) = oos*(s(i-1)+s(i+1)+top(i)+bottom(i)+front(i)+back(i))
    enddo
end subroutine


program J3D

implicit none
double precision :: wct_start,wct_end,cput_start,cput_end,runtime,r
integer :: iter,size,i,j,k,n,t0,t1,t,ofs
double precision, dimension(:,:,:,:), allocatable :: phi 
integer :: argc
character(len=1000) :: arg

argc = command_argument_count()

if(argc.eq.1) then
  call get_command_argument(1,arg)
  read(arg, '(i)') size
else
  print *, 'Usage: ./a.out <size>'
  stop
endif
 
allocate(phi(1:size,1:size,1:size,0:1))

t0=0; t1=1

do k=1,size
   do j=1,size
      do i=1,size
         phi(i,j,k,0)=i*j
         phi(i,j,k,1)=k*j
      enddo
   enddo
enddo

iter=1
runtime=0.d0
do
   call timing(wct_start, cput_start)
   do n=1,iter
      do k=2,size-1
         do j=2,size-1
            call jacobi_line(phi(1,j,k,t1),phi(1,j,k,t0),phi(1,j,k-1,t0), &
                 phi(1,j,k+1,t0),phi(1,j-1,k,t0),phi(1,j+1,k,t0),size)
         enddo
      enddo
      call dummy(phi(1,1,1,t0),phi(1,1,1,t1))
      t=t0; t0=t1; t1=t
   enddo


   call timing(wct_end, cput_end)
   runtime = wct_end-wct_start
   if(runtime.ge.0.2) exit
   iter = iter * 2
enddo

print *,'size: ',size,' iter: ',iter,' MLUP/s: ',dble(iter)*(size-2)*(size-2)*(size-2)/runtime/1000000.d0

end
