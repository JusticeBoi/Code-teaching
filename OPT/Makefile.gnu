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
FLONG	= 
#
#
NOLINK= -c
CLIBS  = -lm
#
all: OPT_C.exe OPT_F.exe

OPT_C.exe: opt_c.o timing.o dummy.o
	$(CC) $(COMP) -o $@ $^ $(CLIBS)

OPT_F.exe: opt_f.o timing.o dummy.o
	$(F90) $(FOMP) -o $@ $^

all: OPT_F.exe OPT_C.exe

%.o: %.c
	$(CC) $(COPTS) $(COMP) $(NOLINK) $<

%.o: %.f90
	$(F90) $(FOPTS) $(FOMP) $(NOLINK) $<

clean:
	rm -f *.o *.exe

