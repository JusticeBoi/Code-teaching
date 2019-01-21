!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! triad.f90 benchmark demo code
! G. Hager, 2010
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
program demo
  implicit none

  interface
      function mysecond ()
          double precision mysecond
      end function mysecond
  end interface

  double precision :: S, E

  S = mysecond()
  call sleep(3)
  E = mysecond()

  print *, "Time: ",E-S,"   sec"
end program demo

