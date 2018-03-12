#
BHOME	=$(PWD)
#
F90	= gfortran
CC	= gcc
#
#
COMP	= #-fopenmp
FOMP	= #-fopenmp
COPTS	=  -Ofast -fargument-noalias
FOPTS	=  -Ofast
FLONG	= -132
#
#
NOLINK= -c
#

all:	SCAN_F.exe SCAN_C.exe

SCAN_F.exe: scan_f.o timing.o
	$(F90) $(FOMP) -o SCAN_F.exe $^ $(LINKF)

SCAN_C.exe: scan_c.o timing.o
	$(CC) $(COMP) -o SCAN_C.exe $^ $(LINKF)

%.o:  %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o:  %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

