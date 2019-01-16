#ifndef pfAStar_h
#define pfAStar_h


#include "class_node.h"
#include "class_map.h"
#include "class_ANode.h"

#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <queue>


typedef std::array<int,2> asLocation ;


// Struct for comparing ANodes by their f value
struct compare_asNodes{
  bool operator()(ANode *left, ANode *right) const {
    return left->Getf() < right->Getf();
  }
};

class pfAStar {

 private:

  // allNodes:
  // sorted by Coordinates <x,y>: <0,0>, <0,1>, ...., <1,0>, <1,1>, ...., <Width,0>, <Width,1>, .... <Width,Heigh>
  std::vector<ANode> allNodes; 

  // Start/Finish Coordinates
  int START_INDEX, FINISH_INDEX;
  
  // Functions:
  void SetNodes(pfMap &map);

  //Heuristic:
  double Pythagoras( asLocation &Pos);
  double Manhatten ( asLocation &Pos);

  
 public:
  
  //Constructors
  pfAStar(pfMap &_map);
  
  // Getter:
  std::vector<ANode> GetNodes() {return allNodes;};
  int GetStartIndex() const {return START_INDEX;};
  
  // Functions:
  // Actual A*-Algorythm
  void solve(std::string HeuristicName);
 
  // Lists:
  std::priority_queue< ANode*, std::vector<ANode*>, compare_asNodes >  openList;
  std::vector<ANode*> closedList;

};
#endif
