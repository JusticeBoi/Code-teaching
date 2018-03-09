
program histo

use, intrinsic :: iso_c_binding
  implicit none

interface
    integer(c_int) function rand_r(seed) bind(c)
    import :: c_int
    integer(c_int), intent(in) :: seed
    end function
end interface

  double precision :: w,sum,x,pi,f,wct_start,wct_end,c
  integer :: i,n
  integer(c_int) :: value,seed
  integer(c_int), dimension(0:15) :: hist

  seed = 123
  do i=0,15
    hist(i) = 0
  enddo

  call timing(wct_start,c)
  do i=1,1000000000
    value = rand_r(seed)
    hist(IAND(value,15)) = hist(IAND(value,15)) + 1
  enddo
  call timing(wct_end,c)

  do i=0,15
    print *, "hist (",i,")",hist(i)
  enddo

  print *, "Time = ",wct_end-wct_start, "seconds"

end program histo

