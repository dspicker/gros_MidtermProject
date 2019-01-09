#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>


/*
For this algorithm pfNode need an additional integer varaiable "cumulative cost"
containing the distance to the starting node.

It also would be helpful if there was a possibility to mark a node as visited,
for example with an additional boolean variable "visited".
Alternatively it would be possible to keep track of visited nodes by storing them
in a container and searching for them at every step (bad performance!)

...
*/

// declaration of helper functions
bool cheapest(pfNode a, pfNode b);      // closest to origin first (use in unvisited)
bool costliest(pfNode a, pfNode b);      // farthest to origin first (use in ??)

typedef std::priority_queue< int*,std::vector<int*>,decltype(&compArr) > intArrPQ;



//algorithm
pfMap* uniformCost(pfMap &map){
// PART1: search target nodes
  intArrPQ unvisited(&cheapest);


// PART2: find optimal path trom start to Target
  intArrPQ visited(&costliest);  // bad name, maybe change afterwards..







/*  some testing
  map.PrintMap();
  std::cout << map.GetNodeAt(1,1) -> wasVisited << std::endl;
*/
  return &map;
}


// definition of helper functions

bool cheapest(int a[], int[]){
  return true;  // TODO: implement condition so that closest is first
}

bool costliest(int a[], int[]){
  return true;  // TODO: implement condition so that furthest is first
}
