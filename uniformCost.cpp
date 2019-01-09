#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>

typedef std::array<int,2> locArr;


/*
For this algorithm pfNode need an additional integer varaiable "cumulative cost"
containing the distance to the starting node.

It also would be helpful if there was a possibility to mark a node as visited,
for example with an additional boolean variable "visited".
Alternatively it would be possible to keep track of visited nodes by storing them
in a container and searching for them at every step (bad performance!)

...
*/

/* TODO
    - add comparison in function cheapest
    - create loop for checking out neighbors (see below for more)
    -
*/

// helper functions
bool wasVisited(locArr loc, std::map<locArr, locArr>visited){
  return (visited.find(loc) != visited.end());
}
bool isWall(locArr loc, pfMap map){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}

void setCumCost(){  // self-explanatory
} // end setCumCost


//algorithm
pfMap* uniformCost(pfMap &map){
  std::map<locArr, int> cumCostMap;
  std::map<locArr, locArr> history;   // map visited locations to predecessor
                                      // also used to check if already

  // using lamda expression for custom compare function, pass cumCostMap from uniformCost scope
  // for more information see: https://en.cppreference.com/w/cpp/language/lambda
  auto cheapest = [cumCostMap](locArr a, locArr b){
    return true;  // TODO: Add proper comparison
  };
  typedef std::priority_queue<locArr, std::vector<locArr>, decltype(cheapest)> locArrPQ;
  locArrPQ unvisitedPQ(cheapest);    // PQ to keep track of unvisited nodes

  // initialize needed location variables
  locArr startLoc;
  locArr targetLoc;
  locArr currentLoc;
  locArr priorLoc;
  locArr neighborLoc;

  startLoc = map.GetStartLoc();
  std::cout << "start: " << startLoc[0] << "," << startLoc[1] << '\n';
  unvisitedPQ.push(startLoc);

  while(!unvisitedPQ.empty()){
    // visit currentLoc
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    //visited.insert(std::make_pair(currentLoc, map.GetNodeAt(currentLoc)->GetWeight()));
    if (currentLoc == targetLoc)
      break;
    //TODO: check if currentLoc in history (if already visited) -> skip to top of loop

    // check neighbors (clockwise)
    neighborLoc = {currentLoc[0], currentLoc[1]+1};
    std::cout << "1. neighbor: " << neighborLoc[0] << "," << neighborLoc[1] << '\n';

    /* TODO:
      overload operator+ for locArr and loop 4 times to handle neighbors
      so that one can do neighborLoc=currentLoc+direction[i]
      where direction = {{0,1},{1,0},{0,-1},{-1,0}}
    */
    neighborLoc = {currentLoc[0]+1, currentLoc[1]};
    neighborLoc = {currentLoc[0], currentLoc[1]-1};
    neighborLoc = {currentLoc[0]-1, currentLoc[1]};
  }

  map.PrintMap();
  return &map;
}
