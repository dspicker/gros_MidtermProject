# THIS IS A COMMENT

# You print stuff like this:
# @echo <Text>

# VARIABLES 
CFLAGS = -Wall -W -O -std=c++11

# EVERY FILE INSERTED HERE WILL BE BUILD IN EXACT THIS ORDER
all: class_node.o class_map.o class_ANode.o test.o test main.o main test2 clean

# EXECUTABLES
test: test.o class_node.o class_ANode.o
		g++ $(CFLAGS) -o test test.o class_node.o class_ANode.o

test2: test2.o class_node.o class_ANode.o class_map.o class_AStar.o
		g++ $(CFLAGS) -o test2 test2.o class_node.o class_ANode.o class_map.o class_AStar.o

main: main.o class_node.o class_map.o
		g++ $(CFLAGS) -o main main.o class_node.o class_map.o



# .O's - mashine language stuff
class_node.o: class_node.cpp class_node.h
		g++ $(CFLAGS) -c class_node.cpp

class_map.o: class_node.h
		g++ $(CFLAGS) -c class_map.cpp

class_ANode.o:  class_node.h class_ANode.h class_ANode.cpp
		g++ $(CFLAGS) -c class_ANode.cpp

class_AStar.o: class_node.h class_map.h
		g++ $(CFLAGS) -c class_AStar.cpp

test.o: test.cpp class_ANode.h
		g++ $(CFLAGS) -c test.cpp 


test2.o: test2.cpp class_map.h class_node.h class_ANode.h class_AStar.h
		g++ $(CFLAGS) -c test2.cpp 

main.o: class_node.h class_map.h
		g++ $(CFLAGS) -c main.cpp 


# CLEAR REPOSITORY AFTER MAKE
clean:
		# 'rm -f' (=force) -> no error if no matching file is found
		# '-' -> makefile does not break after error occurs 
		-rm -f core *.o
		-rm -f *~
		-rm -f *.gch
