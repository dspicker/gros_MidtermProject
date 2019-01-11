#ifndef pfAStar_h
#define pfAStar_h


#include "class_node.h"
#include "class_map.h"
#include "class_ANode.h"

#include <iostream>
#include <map>
#include <array>
#include <vector>

class pfAStar {

 private:

  const pfMap map;

  std::vector<ANode> allNodes; 

  //openlist;
  //closedlist;
  
 public:

  //Constructors
 pfAStar(pfMap &_map): map(_map) {};
  
  //Functions:
  void SetNodes();
  
  //Heuristic:
  //double h( std::array<int,2> ) {


};
#endif
