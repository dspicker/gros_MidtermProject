#ifndef pfNode_h
#define pfNode_h

#include <string>


class pfNode {
protected:
  int type ;   // type of node. 1 wall, 2 grass, 3 forest, 4 start-node, 5 target-node
  int weight;  // depends on the type. grass 1, forest 5, wall -1

  bool isPath = false; 

public:
  // Constructor:
  // Should be used for initializing pfNode
  pfNode(int t);

  //can be used, for createing *pfNode
  pfNode()=default;

  // Getter:
  // Should be const, expecially for using a std::priority_queue
  int GetType() const { return type; }
  int GetWeight() const { return weight; }
  std::string GetTypeName() const; // returns "Wall", "Grass", etc..

  
  // Setter:
  // set the node as a start or end point of the path.
  void SetStart();
  void SetTarget();
  void SetIsPath();
  
  // prints the node to std::cout with an rgb colored whitespace
  void Print();

};



#endif
