#
BHOME	=$(PWD)
#
F90	= gfortran
CC	= gcc
#
#
COMP	= #-fopenmp
FOMP	= #-fopenmp
COPTS	=  -Ofast
FOPTS	=  -Ofast
FLONG	= -132
#
#
NOLINK= -c
LINKF = -lm
#

all:	DIV_F.exe DIV_C.exe

DIV_F.exe: div_f.o timing.o
	$(F90) $(FOMP) -o DIV_F.exe $^ $(LINKF)

DIV_C.exe: div_c.o timing.o
	$(CC) $(COMP) -o DIV_C.exe $^ $(LINKF)

%.o:  %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o:  %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

