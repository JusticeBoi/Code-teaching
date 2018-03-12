program optimize
  
  integer N

  double precision, dimension(:,:), allocatable :: mat,s
  double precision :: val,wct_start,wct_end,cput_start,cput_end,runtime
  integer :: i,j,R,iter
  integer, dimension(:), allocatable :: v
  character(len=32) :: bin,arg

  call get_command_argument(0, bin)
  call get_command_argument(1, arg)
  if (len_trim(arg) == 0) then
    write(*,*) "Usage: ",bin," <size>"
    stop
  endif

  read(arg,*) N
  allocate(mat(N,N),s(N,N),v(N))

  do i=1,N
     v(i) = i
     do j=1,N
        mat(j,i) = (dble(i)*j)/(dble(N)*N)
        s(j,i) = i/dble(N)
     enddo
  enddo

  R=1

  do 
    call timing(wct_start, cput_start)

    do iter=1,R
      
       do i=1,N
          do j=1,N
             val = dble(mod(v(i),256))
             mat(i,j) = s(i,j)*(sin(val)*sin(val)-cos(val)*cos(val))
          enddo
       enddo
       if(mat(2,2)<-1000.d0) call dummy(mat(2,2))
    enddo
    
    call timing(wct_end, cput_end)
    runtime = wct_end-wct_start
    R = R + R

    if(runtime.ge.0.2d0) exit

 enddo
  
 R=R/2;
    
 print *,"Performance: ", dble(R)*dble(N)*N/runtime/1000000.d0," MIt/s"


end program optimize
