CFLAGS = -Wall -W -O -std=c++11

all: main.o class_map.o class_node.o
		g++ $(CFLAGS) -o pathfinder main.o class_map.o class_node.o

main: main.cpp
		g++ $(CFLAGS) -c main.cpp

class_map: class_map.cpp class_map.h
		g++ $(CFLAGS) -c class_map.cpp

class_node: class_node.cpp class_node.h
		g++ $(CFLAGS) -c class_node.cpp

#class_Square: class_Square.cpp class_Square.h
#	g++ $(CFLAGS) -c class_Square.cpp

clean:
		rm -f core *.o
		rm *~
