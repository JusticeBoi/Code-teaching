CC  = icc
CXX = icpc
FC  = ifort
LINKER = $(CC)

#CFLAGS   = -fast -std=c99 
CFLAGS   = -O3 -std=c99 
CXXFLAGS = $(CFLAGS)
FCFLAGS  = 
LFLAGS   =  -vec-report0
DEFINES  = -D_GNU_SOURCE
INCLUDES = 
LIBS     = 


