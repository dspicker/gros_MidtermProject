#ifndef pfAStar_h
#define pfAStar_h


#include "class_node.h"
#include "class_map.h"
#include "class_asNode.h"

#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <queue>


typedef std::array<int,2> asLocation ;

// Struct for comparing asNodes by their f value
// Needed for sorting the priority_queue of asNode*s
struct compare_asNodes{
  bool operator()(asNode *left, asNode *right) const {
    return *left->Getf() > *right->Getf();
  }
};

class pfAStar {

 private:

  // allNodes:
  // sorted by Coordinates <x,y>: <0,0>, <0,1>, ...., <1,0>, <1,1>, ...., <Width,0>, <Width,1>, .... <Width,Heigh>
  std::vector<asNode> allNodes;

  // Index of Start/Finish in allNodes
  int START_INDEX, FINISH_INDEX;
  asLocation FINISH_COORD; //Also the Finish Coordinates, beacause calculating Heuristics gets easier

  // Functions:
  void SetNodes(pfMap &map); // Needed for Initialisation

  // Lists:
  std::priority_queue< asNode*, std::vector<asNode*>, compare_asNodes >  openList;
  std::vector<asNode*> PathNodes;

  //Heuristics:
  double Minimum  ( asLocation &Pos);
  double Supremum  ( asLocation &Pos);
  double Manhattan ( asLocation &Pos);
  double Euklid    ( asLocation &Pos);

  // Save Input Map by reference, hence it can be updated for plotting.
  pfMap* MapPtr;


 public:

  //Constructors
  pfAStar(pfMap &_map);

  // Getter:
  // Just needed for Debugging
  std::vector<asNode> GetNodes() {return allNodes;};
  int GetStartIndex() const {return START_INDEX;};

  // Functions:
  void solve(std::string HeuristicName, bool animate = false); // Actual A*-Algorithm
  void UpdateMap(); // For Updating and Plotting the Input Map

};
#endif
