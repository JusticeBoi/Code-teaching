#
BHOME	=$(PWD)
#
F90	= gfortran
CC	= gcc
#
#
COMP	= #-fopenmp
FOMP	= #-fopenmp
COPTS	=  -Ofast -fno-inline -fargument-noalias
FOPTS	=  -Ofast -fno-inline 
FLONG	= -132
#
#
NOLINK= -c
#

all: J3D_F.exe J3D_C.exe

J3D_F.exe: j3d_f.o timing.o dummy.o
	$(F90) $(FOMP) -o J3D_F.exe j3d_f.o timing.o dummy.o

J3D_C.exe: j3d_c.o timing.o dummy.o
	$(CC) $(COMP) -o J3D_C.exe j3d_c.o timing.o dummy.o

%.o: %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o: %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

