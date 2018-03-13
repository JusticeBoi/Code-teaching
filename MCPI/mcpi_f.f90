program mcpi

  use, intrinsic :: iso_c_binding
  interface
     integer(c_int) function rand_r(seed) bind(c)
       import :: c_int
       integer(c_int), intent(in) :: seed
     end function rand_r
  end interface
  integer(c_int) :: seed
  integer(c_int),parameter :: RAND_MAX=2147483647
  double precision :: x,y,wcs,wce,c,pi
  double precision, parameter :: M_PI=3.14159265358979d0
  integer :: i,count
  integer, parameter :: NN=342000000

  count=0

  call timing(wcs, c)

  seed = 2

  do i=1,NN
    x = rand_r(seed)/DBLE(RAND_MAX)
    y = rand_r(seed)/DBLE(RAND_MAX)
    if(sqrt(x*x+y*y) <1.d0) count=count+1
  enddo


  pi = 4.d0*DBLE(count)/NN 

  call timing(wce, c)
 
  write(*,*) 'Time: ',wce-wcs,' accuracy: ',abs(M_PI-pi)/M_PI

end program mcpi


  
