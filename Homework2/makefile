
CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lm -lgsl -lgslcblas

HEADERS = BodyCenteredCubicLattice.h SimpleCubicLattice.h LatticeNode.h
OBJECTS = BodyCenteredCubicLattice.o SimpleCubicLattice.o LatticeNode.o main.o
PROGRAM = HW2

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c


