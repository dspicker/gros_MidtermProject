#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>
// #include <climit> // INT_MAX for

typedef std::array<int,2> locArr;

bool debug = false;  // display test output at different stages of algorithm

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
    - reconsider where exactly the cumCost is taken into accoutn
      is the weight of currentLoc part of its cumCost ???
      (the way it is implemented now: yes, but I'm not sure if this is the
      best decision anymore, it might not make a difference..?)

      .. yeah it should not make a difffernece. It's eighther starting width
      cumCost=0 of at the startLoc and taking the weight of the target node
      into account
      OR
      it's the other way arround, starting with cumCost=1, which is not very
      sensical..
*/

// helper functions
bool wasVisited(std::map<locArr, locArr> history, locArr loc){
  return history.count(loc);
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
int  getCumCost(std::map<locArr, int> &myMap, locArr loc){
  return myMap.at(loc);
}
// only change set-/getCumCost if cumCost can be stored in node directly
locArr addLocArr(locArr &a, locArr &b){
  locArr res;
  for(int i=0; i<2;i++)
    res[i] = a[i] + b[i];
  return res;
}


//algorithm
pfMap* uniformCost(pfMap &map){
  std::map<locArr, int> cumCostMap;
  std::map<locArr, locArr> history;   // link visited locations to predecessor
                                      // also used to check if already

  // using lamda expression for custom compare function, pass cumCostMap from uniformCost scope
  // for more information see: https://en.cppreference.com/w/cpp/language/lambda
  auto cheapest = [&cumCostMap](locArr a, locArr b){
    // change < to > (or Vice Versa, I dont know yet)
    // to change from breadth first to depth first!
    return (cumCostMap.at(a) > cumCostMap.at(b));
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
  int currentCumCost;

  std::array<locArr,4> directions {{{0,1},{1,0},{0,-1},{-1,0}}};


  // set cumCost for start node, push into PQ
  setCumCost(cumCostMap, startLoc, 0);
  unvisitedPQ.push(startLoc);
  if (debug){std::cout << "DEBUG: start:    " << startLoc[0] << "," << startLoc[1] << '\n';}
  previousLoc = startLoc; // handle border case of first iteration where ther is no previousLoc

  // central loop (algorithm)
  while(!unvisitedPQ.empty()){
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    if(wasVisited(history,currentLoc))  // abourt iteration if already visited
      continue;

    history[currentLoc] = previousLoc;
    previousLoc = currentLoc;

    if (currentLoc == targetLoc){        // end loop if target is found
      if(debug){std::cout << "DEBUG: target reached!" << '\n';}
      break;
    }

    // check neigbors of current node
    if(debug){std::cout << "DEBUG: current: " << currentLoc[0] << "," << currentLoc[1] << '\n';}
    for(auto direction : directions){
      neighborLoc = addLocArr(currentLoc, direction);
      if(isWall(map, neighborLoc) | wasVisited(history, neighborLoc))  // reduncandy
        continue;
        /* reduncandy!:
             remove reduncandy becuaes this is also checked at start of while-loop
             maybe try to check value and handly error if key invalid?

             An alternavive would be to not check wasVisited at all here
             because cumCost wouldn't be updated then anyways..
        */



      /* IMPORTANT: make sure NOT to overwrite a smaller cumCost already entered in cumCostMap!!!
      // Also there is some out of range problem ..
      */
      currentCumCost = getCumCost(cumCostMap, currentLoc);
      neighborCumCost = currentCumCost + map.GetNodeAt(neighborLoc)->GetWeight();

      // This is not right ATM
      if( !cumCostMap.count(neighborLoc)){
        setCumCost(cumCostMap, neighborLoc, neighborCumCost); // <- does not work as intended!
        unvisitedPQ.push(neighborLoc);
      }
      else if(getCumCost(cumCostMap,neighborLoc) > neighborCumCost){
        setCumCost(cumCostMap, neighborLoc, neighborCumCost); // <- does not work as intended!
        unvisitedPQ.push(neighborLoc);
      }
      if(debug){std::cout << "DEBUG: neighbor:  " << neighborLoc[0] << "," << neighborLoc[1] << "\n";}
    }
  }
  if(debug){std::cout << "DEBUG: cumCost of target: " << getCumCost(cumCostMap, targetLoc) << '\n';}
  map.PrintMap();
  return &map;
}

// function to draw path into Object of pfMap
void drawPath();
