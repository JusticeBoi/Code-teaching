
program scan
    implicit none
    double precision :: wctstart,wctend,cpustart,cpuend
    double precision, allocatable, dimension(:,:) :: a,b,c
    integer :: n,niter,k,i


    read *,n
    allocate(a(n,n),b(n,n),c(n,n))

    a=1.5d0
    b=0.03d0
    c=0.d0
    
    niter = 1

    do

        call timing(wctstart,cpustart)
        do k=1,niter

!   PUT YOUR CODE HERE
           call mmm(a,b,c,n)

           
        enddo

        call timing(wctend,cpuend)

        if(wctend-wctstart .ge. 0.2d0) exit
        niter = niter*2
    enddo

    write(*,*) 'Total walltime: ',wctend-wctstart
    write(*,*) 'Perf: ',2.0*n*n*n/(wctend-wctstart)*1.d-6,' Mflop/s' 


end

subroutine mmm(a,b,c,n)
  integer :: n
  double precision :: a(n,n),b(n,n),c(n,n)
  
  integer :: i,j,k
  
!  !dir$ unroll_and_jam(4)
  !dir$ block_loop factor(128)
  do k=1,n,4
!     !dir$ block_loop factor(100) level(1)
!     !dir$ unroll_and_jam(4)
     do j=1,n,4
!        !dir$ block_loop factor(128) level(1)
        !dir$ unroll(8)
        do i=1,n
           c(i,k+0) = c(i,k+0) + a(j+0,k+0) * b(i,j+0)
           c(i,k+0) = c(i,k+0) + a(j+1,k+0) * b(i,j+1)
           c(i,k+0) = c(i,k+0) + a(j+2,k+0) * b(i,j+2)
           c(i,k+0) = c(i,k+0) + a(j+3,k+0) * b(i,j+3)

           c(i,k+1) = c(i,k+1) + a(j+0,k+1) * b(i,j+0)
           c(i,k+1) = c(i,k+1) + a(j+1,k+1) * b(i,j+1)
           c(i,k+1) = c(i,k+1) + a(j+2,k+1) * b(i,j+2)
           c(i,k+1) = c(i,k+1) + a(j+3,k+1) * b(i,j+3)

           c(i,k+2) = c(i,k+2) + a(j+0,k+2) * b(i,j+0)
           c(i,k+2) = c(i,k+2) + a(j+1,k+2) * b(i,j+1)
           c(i,k+2) = c(i,k+2) + a(j+2,k+2) * b(i,j+2)
           c(i,k+2) = c(i,k+2) + a(j+3,k+2) * b(i,j+3)

           c(i,k+3) = c(i,k+3) + a(j+0,k+3) * b(i,j+0)
           c(i,k+3) = c(i,k+3) + a(j+1,k+3) * b(i,j+1)
           c(i,k+3) = c(i,k+3) + a(j+2,k+3) * b(i,j+2)
           c(i,k+3) = c(i,k+3) + a(j+3,k+3) * b(i,j+3)
        enddo
     enddo
  enddo
  

end subroutine mmm
    
