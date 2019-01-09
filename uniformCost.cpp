#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>


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
bool  cheapest(std::array<int,2> a, std::array<int,2> b);     // cheapest first
bool costliest(std::array<int,2> a, std::array<int,2> b);     // costliest first

// ture if visited or wall respectively
bool wasVisited(std::array<int,2> loc, std::map<std::array<int,2>, int> visited);
bool isWall(std::array<int,2> loc);



typedef std::priority_queue<std::array<int,2>, std::vector<std::array<int,2>>, decltype(&cheapest)> intArrPQ;


//algorithm
pfMap* uniformCost(pfMap &map){
// PART1: search target nodes

  intArrPQ unvisitedPQ(&cheapest);          // PQ to keep track of unvisited nodes
  std::map<std::array<int,2>, int> visited; // map to keep track of visited nodes and their cumulative cost

  std::array<int,2> startLoc;
  std::array<int,2> targetLoc;
  std::array<int,2> currentLoc;
  std::array<int,2> neighborLoc;

  startLoc = map.GetStartLoc();
  unvisitedPQ.push(startLoc);

  while(!unvisitedPQ.empty()){
    // visit currentLoc 
    currentLoc = unvisitedPQ.top();
    visited.insert(std::make_pair(currentLoc, map.GetNodeAt(currentLoc)->GetWeight()));
/*
    // check neighbors (clockwise),if possible assign cumulative cost and add to unvisitedPQ
    neighborLoc = {currentLoc[0], currentLoc[1]+1};
    if( !(wasVisited(neighborLoc, visited) | isWall(neighborLoc, *map))){
      std::cout << "it works so far?!" << '\n';
    }

    //  handle these analog to neighbor one
    neighborLoc = {currentLoc[0]+1, currentLoc[1]};

    neighborLoc = {currentLoc[0], currentLoc[1]-1};

    neighborLoc = {currentLoc[0]-1, currentLoc[1]};


*/






    if (currentLoc == targetLoc)
      break;




    unvisitedPQ.pop();
  }







// PART2: find optimal path trom start to Target
  intArrPQ visitedPQ(&costliest);  // bad name, maybe change afterwards..







/*  some testing
  map.PrintMap();
  std::cout << map.GetNodeAt(1,1) -> wasVisited << std::endl;
*/
  map.PrintMap();
  return &map;
}


// definition of helper functions

bool cheapest(std::array<int,2> a, std::array<int,2> b){
  return true;  // TODO: implement condition so that cheapest is first
}

bool costliest(std::array<int,2> a, std::array<int,2> b){
  return true;  // TODO: implement condition so that costliest is first
}

bool wasVisited(std::array<int,2> loc, std::map<std::array<int,2>, int>visited){
  return (visited.find(loc) == visited.end());
}

bool isWall(std::array<int,2> loc, pfMap &map){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}
