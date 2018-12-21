CFLAGS = -Wall -W -O -std=c++11

all: main.o
  g++ $(CFLAGS) -o pathfinder main.o

main: main.cpp
	g++ $(CFLAGS) -c main.cpp

#class_Square: class_Square.cpp class_Square.h
#	g++ $(CFLAGS) -c class_Square.cpp

clean:
	rm -f core *.o
	rm *~
