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
FOPTS	=  -Ofast -xAVX -fno-alias -fno-inline
FLONG	= -132
#
#
NOLINK= -c
#

all:	SCAN_F.exe

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

