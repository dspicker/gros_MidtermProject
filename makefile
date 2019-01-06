# THIS IS A COMMENT

# You print stuff like this:
# @echo <Text>

# VARIABLES 
CFLAGS = -Wall -W -O -std=c++11

# EVERY FILE INSERTED HERE WILL BE BUILD
all: class_node.o class_map.o class_ANode.o test.o test main.o main clean

# EXECUTABLES
test: test.o class_node.o class_ANode.o
		g++ $(CFLAGS) -o test test.o class_node.o class_ANode.o

main: main.o class_node.o class_map.o
		g++ $(CFLAGS) -o main main.o class_node.o class_map.o



# .O's - mashine language stuff
class_node.o: class_node.cpp class_node.h
		g++ $(CFLAGS) -c class_node.cpp

class_map.o: class_node.h
		g++ $(CFLAGS) -c class_map.cpp

class_ANode.o:  class_node.h class_ANode.h class_ANode.cpp
		g++ $(CFLAGS) -c class_ANode.cpp


test.o: test.cpp class_ANode.h
		g++ $(CFLAGS) -c test.cpp 

main.o: class_node.h class_map.h
		g++ $(CFLAGS) -c main.cpp 


# CLEAR REPOSITORY AFTER MAKE
clean:
		# 'rm -f' (=force) -> no error if no matching file is found
		# '-' -> makefile does not break after error occurs 
		-rm -f core *.o
		-rm -f *~
		-rm -f *.gch
