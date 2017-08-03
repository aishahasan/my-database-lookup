CC  = gcc
CXX = g++

INCLUDES = -I../../lab3/solutions/part1
CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g -L../../lab3/solutions/part1
LDLIBS = -lmylist

mdb-lookup: mdb-lookup.o

mdb-lookup.o: mdb-lookup.c mdb.h


.PHONY: clean
clean:
  rm -f *.o a.out mdb-lookup

.PHONY: valgrind
valgrind: mdb-lookup 
  valgrind --leak-check=full --track-origins=yes ./mdb-lookup my-mdb

.PHONY: all
all: clean
