CXX ?= g++

FLAGS =

ifeq ($(CXX), g++)
	FLAGS = -std=c++0x -Wall -Winline -Wshadow -W -O3 -fopenmp -march=native
else
	FLAGS = -std=c++0x -Wall -Winline -Wshadow -W -O3 -fno-alias -qopenmp -xHOST
endif

INCLUDES =-Iinclude
LDFLAGS =
LIBS =

#EXTRA_FLAGS :=
CXXFLAGS = $(FLAGS) $(EXTRA_FLAGS)

all: test perf

perf: perf.o Grid.o PDE.o Solver.o timer.o
	$(CXX) $(CXXFLAGS) -o perf Grid.o PDE.o Solver.o perf.o timer.o $(LDFLAGS) $(LIBS)

test: test.o Grid.o PDE.o Solver.o timer.o
	$(CXX) $(CXXFLAGS) -o test Grid.o PDE.o Solver.o test.o timer.o $(LDFLAGS) $(LIBS)

perf.o: src/perf.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/perf.cpp

test.o: src/test.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/test.cpp

Solver.o: src/Solver.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/Solver.cpp

PDE.o: src/PDE.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/PDE.cpp

Grid.o: src/Grid.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/Grid.cpp

timer.o: src/timer.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) src/timer.cpp


clean:
	@$(RM) -rf *.o perf test
