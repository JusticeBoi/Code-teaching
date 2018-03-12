#
#	Makefile for Intel9.1 compiler
#
BHOME	=$(PWD)
#
F90	= gfortran
CC	= gcc
#
#
COMP	= #-qopenmp
FOMP	= #-qopenmp
COPTS	=  -Ofast -fargument-noalias
FOPTS	=  -Ofast
FLONG	= -132
#
#
NOLINK= -c
#

all: RAY_F.exe RAY_C.exe

RAY_C.exe: raytrace_c.o timing.o
	$(CC) $(COMP) -o RAY_C.exe raytrace_c.o timing.o

RAY_F.exe: raytrace_f.o timing.o
	$(F90) $(COMP) -o RAY_F.exe raytrace_f.o timing.o

%.o: %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o: %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe *.mod

