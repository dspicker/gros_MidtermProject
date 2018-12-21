#ifndef pfNode_h
#define pfNode_h

#include <string>

class pfNode {
private:
  int type ;   // type of node. 1 wall, 2 grass, 3 forest
  int weight;  // depends on the type. grass 1, forest 5, wall -1


public:
  // constructor
  pfNode(int t);


  int GetType(){ return type; }
  int GetWeight(){ return weight; }

  std::string GetTypeName() ;

  void Print();

};



#endif
