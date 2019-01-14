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

  pfMap map;

  // allNodes:
  // sorted by Coordinates <x,y>: <0,0>, <0,1>, ...., <1,0>, <1,1>, ...., <Width,0>, <Width,1>, .... <Width,Heigh>
  std::vector<ANode> allNodes; 

  //openlist;
  //closedlist;
  
 public:

  //Constructors
 pfAStar(pfMap &_map): map(_map) {
    SetNodes();  
  };
  
  //Functions:
  void SetNodes();
  pfMap* GetMap() {return &map;}; //no const here! 
  std::vector<ANode> GetNodes() {return allNodes;};

  //Heuristic:
  //double h( std::array<int,2> ) {


};
#endif
