
program scan
    implicit none
    double precision :: wctstart,wctend,cpustart,cpuend
    integer :: niter,k,i

    niter = 1
    do

        call timing(wctstart,cpustart)
        do k=1,niter

!   PUT YOUR CODE HERE

        enddo

        call timing(wctend,cpuend)

        if(wctend-wctstart .ge. 0.2d0) exit
        niter = niter*2
    enddo

    write(*,*) 'Total walltime: ',wctend-wctstart


end

