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

all:	MCPI_F.exe MCPI_C.exe

MCPI_F.exe: mcpi_f.o timing.o
	$(F90) $(FOMP) -o MCPI_F.exe $^ $(LINKF)

MCPI_C.exe: mcpi_c.o timing.o
	$(CC) $(COMP) -o MCPI_C.exe $^ $(LINKF)

%.o:  %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o:  %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

