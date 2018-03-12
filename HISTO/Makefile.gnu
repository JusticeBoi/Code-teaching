#
BHOME	=$(PWD)
#
F90	= ifort
CC	= icc
#
#
COMP	= #-qopenmp
FOMP	= #-qopenmp
COPTS	=  -O3 -xHOST -fno-alias
FOPTS	=  -O3 -xHOST -fno-alias
FLONG	= -132
#
#
NOLINK= -c
#

all:	HISTO_F.exe HISTO_C.exe

HISTO_F.exe: histo_f.o timing.o
	$(F90) $(FOMP) -o HISTO_F.exe $^ $(LINKF)

HISTO_C.exe: histo_c.o timing.o
	$(CC) $(COMP) -o HISTO_C.exe $^ $(LINKF)

%.o:  %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o:  %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

