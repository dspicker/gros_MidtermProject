#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>

typedef std::array<int,2> locArr;

bool debug = true;  // display test output at different stages of algorithm

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
    - overlad operator+ for type locArr
    - add function to pfMap class to set start and target locations ALSO
      in the varialbes start_loc and target_loc of pfMap
      (otherwise it is impossible to set them..)
*/

// helper functions
bool wasVisited(std::map<locArr, locArr> history, locArr loc){
  return (history.find(loc) != history
  .end());
}
bool isWall(pfMap map, locArr loc){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}
void setHistory(std::map<locArr, locArr> &myMap, locArr current, locArr previous){
  myMap[current] = previous;
}
void setCumCost(std::map<locArr, int> &myMap, locArr loc, int cost){
  myMap[loc] = cost;
}
int getCumCost(std::map<locArr, int> &myMap, locArr loc){
  return myMap[loc];
}
// only change set-/getCumCost if cumCost can be stored in node directly


//algorithm
pfMap* uniformCost(pfMap &map){
  std::map<locArr, int> cumCostMap;
  std::map<locArr, locArr> history;   // link visited locations to predecessor
                                      // also used to check if already

  // using lamda expression for custom compare function, pass cumCostMap from uniformCost scope
  // for more information see: https://en.cppreference.com/w/cpp/language/lambda
  auto cheapest = [cumCostMap](locArr a, locArr b){
    // change < to > (or Vice Versa, I dont know yet)
    // to change from breadth first to depth first!
    return (cumCostMap.at(a) < cumCostMap.at(b));
  };
  std::priority_queue<locArr, std::vector<locArr>, decltype(cheapest)> unvisitedPQ(cheapest);
  // ^ PQ to keep track of unvisited nodes

  // initialize needed variables (and maybe not so needed variables)
  locArr startLoc = map.GetStartLoc();
  locArr targetLoc = map.GetTargetLoc();

  locArr currentLoc;
  locArr neighborLoc;
  locArr previousLoc;

  int neighborCumCost;
  int currentCumCost;  // unneeded?

  int directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};  // to iterate over neighbors easily


  // set cumCost for start node, push into PQ
  setCumCost(cumCostMap, startLoc, 0);
  unvisitedPQ.push(startLoc);
  if (debug){std::cout << "DEBUG: start: " << startLoc[0] << "," << startLoc[1] << '\n';}
  previousLoc = startLoc; // handle border case of first iteration where ther is no previousLoc

  // central loop (algorithm)
  while(!unvisitedPQ.empty()){
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    if(wasVisited(history,currentLoc))  // abourt iteration if already visited
      continue;
    history[currentLoc] = previousLoc;
    if (currentLoc == targetLoc)        // end loop if target is found
      break;


    /* TODO:
      overload operator+ for locArr and loop 4 times to handle neighbors
      so that one can do neighborLoc=currentLoc+direction[i]
      where direction = {{0,1},{1,0},{0,-1},{-1,0}}
    */
    for(auto direction : directions){
      std::cout << "iteration over neighbors works!" << '\n';
      // neighborLoc = currentLoc + direction;
      if(!isWall(map, neighborLoc))
        continue;
      else
        currentCumCost = getCumCost(cumCostMap, currentLoc);
        neighborCumCost = currentCumCost + map.GetNodeAt(neighborLoc)->GetWeight();
        setCumCost(cumCostMap, neighborLoc, neighborCumCost);

    }



    // check neighbors (clockwise)
    neighborLoc = {currentLoc[0], currentLoc[1]+1};
    if(debug){std::cout << "DEBUG: 1. neighbor: " << neighborLoc[0] << "," << neighborLoc[1] << '\n';}
    neighborLoc = {currentLoc[0]+1, currentLoc[1]};
    neighborLoc = {currentLoc[0], currentLoc[1]-1};
    neighborLoc = {currentLoc[0]-1, currentLoc[1]};

    previousLoc = currentLoc;
  }

  map.PrintMap();
  return &map;
}

// function to draw path into Object of pfMap
void drawPath();
