#include "class_map.h"

#include <iostream>
#include <vector>
#include <queue>


/*
For this algorithm pfNode need an additional integer varaiable "distance"
containing the distance to the starting node.

It also would be helpful if there was a possibility to mark a node as wasVisited,
for example with an additional boolean variable "visited".
Alternatively it would be possible to keep track of visited nodes by storing them
in a container and searching for them at every step (bad performance!)

...
*/

// declaration of helper functions
bool justType(pfNode a, pfNode b);      // only! for decltype to get the correct type
bool lightest(pfNode a, pfNode b);      // closest to origin first (use in unvisited)
bool heaviest(pfNode a, pfNode b);      // farthest to origin first (use in ??)

typedef std::priority_queue<pfNode,std::vector<pfNode>, decltype(&justType)> pfNodePQ;



//algorithm
pfMap* uniformCost(pfMap &map){
// PART1: search target nodes
  pfNodePQ unvisited(&lightest);


// PART2: find optimal path trom start to Target
  pfNodePQ visited(&heaviest);  // bad name, maybe change afterwards..







/*  some testing
  map.PrintMap();
  std::cout << map.GetNodeAt(1,1) -> wasVisited << std::endl;
*/
  return &map;
}


// definition of helper functions

bool justType(pfNode a, pfNode b){
  return true;
} // only for decltype (do not use elsewhere!)

bool lightest(pfNode a, pfNode b){
  return true;  // TODO: implement condition so that closest is first
}

bool heaviest(pfNode a, pfNode b){
  return true;  // TODO: implement condition so that furthest is first
}
