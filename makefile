

# VARIABLES
CFLAGS = -Wall -W -O -std=c++11

# EVERY PART INSERTED HERE WILL BE EXECUTED IN EXACT THIS ORDER
TARGETS = main visualize testPerformance testAStar plotGnuMap clean
all: $(TARGETS)
$(info make: $(TARGETS) )

# EXECUTABLES (GETTING LINKED)
main: main.o
		g++ $(CFLAGS) -o pathfinder main.o class_node.o class_map.o class_asNode.o class_AStar.o

testAStar: testAStar.o
		g++ $(CFLAGS) -o testAStar testAStar.o class_node.o class_asNode.o class_map.o class_AStar.o

visualize: visualize.o
		g++ $(CFLAGS) -o visualize visualize.o class_AStar.o class_node.o class_map.o class_asNode.o

testPerformance: testPerformance.o
		g++ $(CFLAGS) -o testPerformance testPerformance.o class_AStar.o class_node.o class_map.o  class_asNode.o


plotGnuMap: plotGnuMap.o
		g++ $(CFLAGS) -o plotGnuMap plotGnuMap.o class_node.o class_map.o class_AStar.o class_asNode.o


###### classes
class_node.o: class_node.cpp class_node.h
		g++ $(CFLAGS) -c class_node.cpp

class_map.o: class_node.h class_map.cpp
		g++ $(CFLAGS) -c class_map.cpp

class_asNode.o:	class_node.h class_asNode.cpp class_asNode.h
		g++ $(CFLAGS) -c class_asNode.cpp

class_AStar.o: 	class_node.h class_map.h class_asNode.h GnuGif.cpp
		g++ $(CFLAGS) -c class_AStar.cpp

CLASSES = class_node.o class_map.o class_asNode.o class_AStar.o
ALGORITHMS = uniformCost.cpp breadthfirst.cpp greedyBestFirst.cpp

##### files to link
testAStar.o: testAStar.cpp $(CLASSES)
		g++ $(CFLAGS) -c testAStar.cpp

main.o: main.cpp $(CLASSES) $(ALGORITHMS)
		g++ $(CFLAGS) -c main.cpp

visualize.o: visualize.cpp $(CLASSES) $(ALGORITHMS)
		g++ $(CFLAGS) -c visualize.cpp

testPerformance.o: testPerformance.cpp $(CLASSES) $(ALGORITHMS)
		g++ $(CFLAGS) -c testPerformance.cpp


plotGnuMap.o: plotGnuMap.cpp $(CLASSES)
		g++ $(CFLAGS) -c plotGnuMap.cpp


# CLEAR REPOSITORY AFTER MAKE
# 'rm -f' (=force) -> no error if no matching file is found
# '-' -> makefile does not break after error occurs

clean:
		-rm -f core *.o
		-rm -f *~
		-rm -f *.gch
