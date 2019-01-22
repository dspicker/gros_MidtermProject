# THIS IS A COMMENT

# You print stuff like this:
# @echo <Text>

# VARIABLES
CFLAGS = -Wall -W -O -std=c++11

# EVERY PART INSERTED HERE WILL BE EXECUTED IN EXACT THIS ORDER
all: class_node.o class_map.o class_asNode.o class_AStar.o testAStar main clean

# EXECUTABLES (GETTING LINKED)
main: main.o breadthfirst.cpp uniformCost.cpp class_AStar.o class_node.o class_map.o
		g++ $(CFLAGS) -o pathfinder main.o class_node.o class_map.o

testAStar: testAStar.o class_node.o class_asNode.o class_map.o class_AStar.o
		g++ $(CFLAGS) -o testAStar testAStar.o class_node.o class_asNode.o class_map.o class_AStar.o

# .O's - mashine language stuff
class_node.o: class_node.cpp class_node.h
		g++ $(CFLAGS) -c class_node.cpp

class_map.o: class_node.h
		g++ $(CFLAGS) -c class_map.cpp

class_asNode.o:  class_node.h class_asNode.h class_asNode.cpp
		g++ $(CFLAGS) -c class_asNode.cpp

class_AStar.o: class_node.h class_map.h
		g++ $(CFLAGS) -c class_AStar.cpp

testAStar.o: testAStar.cpp class_AStar.h class_map.h
		g++ $(CFLAGS) -c testAStar.cpp

main.o: main.cpp breadthfirst.cpp uniformCost.cpp class_AStar.h class_node.h class_map.h
		g++ $(CFLAGS) -c main.cpp


# CLEAR REPOSITORY AFTER MAKE
# 'rm -f' (=force) -> no error if no matching file is found
# '-' -> makefile does not break after error occurs

clean:
		-rm -f core *.o
		-rm -f *~
		-rm -f *.gch
