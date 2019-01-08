#include "class_map.h"

#include <iostream>
#include <vector>
#include <queue>

/*
For this algorithm pfNodes need an additional integer varaiable "distance"
containing the distance to the starting node.

It also would be helpful if there was a possibility to mark a node as wasVisited,
for example with an additional boolean variable "visited".
Alternatively it would be possible to keep track of visited nodes by storing them
in a container and searching for them at every step (bad performance!)

...
*/

// declaration of helper functions
bool compare(pfNode &a, pfNode &b);



//algorithm
pfMap* uniformCost(pfMap &map){
/*  some testing
  std::priority_queue<pfNodes, std::vector<pfNodes>, decltype(&comp)
  map.PrintMap();
  std::cout << map.GetNodeAt(1,1) -> wasVisited << std::endl;
*/
  return &map;
}


// definition of helper functions
bool compare(pfNode &a, pfNode &b){
  return ?  // how exactly should they be prioritised?
}
