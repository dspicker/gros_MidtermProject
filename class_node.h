#ifndef pfNode_h
#define pfNode_h

#include <string>

class pfNode {
private:
  int type ;   // type of node. wall, grass, forest
  int weight;  // depends on the type. grass 1, forest 5, wall -1


public:
  // constructor
  pfNode(int t);

  int GetType(){ return type; }
  int GetWeight(){ return weight; }

  std::string GetTypeName() ;

};



#endif
