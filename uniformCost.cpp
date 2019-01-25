#include "class_map.h"
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>

typedef std::array<int,2> locArr;
bool ucDebug = false;  // display test output at different stages of algorithm

/* TODO
    - animation in terminal
    - delete ucDrawKnown
    - write setter funciton for f in pfNode.cpp
    - use f of pfNodes to store cumCost instead of cumCostMap?
    - get rid of cumCostMap? <- make up for performance reduction of altering map!
    - store pointer to node in usDrawKnown
    - add functionality to measure time taken to find the targetLoc
    - use 2D array 'cumCostArr' instead of cumCostMap for better performance?
      (using library arrays, initializing every location with INT_MAX)
*/

// helper function (for easy adaptation to changes in pfMap and pfNode)
bool ucIsKnown(std::map<locArr, locArr> &myHistory, locArr loc){
  return myHistory.count(loc);
}
bool ucIsWall(pfMap map, locArr loc){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}
void ucSetHistory(std::map<locArr, locArr> &myHistory,
                  locArr neighbor, locArr current){
  myHistory[neighbor] = current;
}
void ucSetCumCost(std::map<locArr, int> &myCumCostMap, locArr loc, int cost){
  // change to only set cumCost, if there is no (lower) value saved already??
  myCumCostMap[loc] = cost;
}
int ucGetCumCost(std::map<locArr, int> &myCumCostMap, locArr loc){
  return myCumCostMap.at(loc);
}
locArr ucAddLocArr(locArr &a, locArr &b){
  locArr res;
  res[0] = a[0] + b[0];
  res[1] = a[1] + b[1];
  return res;
}

// functions for visualisation (call in main)
void ucDrawPath(std::map<locArr, locArr> &myHistory, pfMap &map){
  locArr targetLoc = map.GetTargetLoc();
  locArr startLoc  = map.GetStartLoc();
  locArr currentLoc = targetLoc;
  locArr previousLoc;
  if( myHistory.find(targetLoc) == myHistory.end() ){ // check if target found, abourt if not
    std::cout << "UniformCost: Target not found!" << '\n';
    return;
  }
  // loop through linked locations starting at target location
  while(true){
    previousLoc = myHistory.at(currentLoc);
    if(ucDebug){
      std::cout << "DEBUG (ucDrawPath): currentLoc:  " << currentLoc[0] << ","
                << currentLoc[1] << '\n';
      std::cout << "DEBUG (ucDrawPath): previousLoc: " << previousLoc[0] << ","
                << previousLoc[1] << '\n';
      std::cout << std::endl;
    }
    if(previousLoc == startLoc)
      break;
    map.GetNodeAt(previousLoc)->SetIsPath();
    currentLoc = previousLoc;
  }
}
void ucDrawKnown(std::map<locArr, locArr> &myHistory, pfMap &map){ // REDUNDANT!!!
  locArr startLoc  = map.GetStartLoc();
  locArr targetLoc = map.GetTargetLoc();
  for(auto const &it : myHistory){
    locArr loc = it.first;
    if(loc != startLoc && loc != targetLoc){  // ignore start and target locations
      pfNode* pt2Node = map.GetNodeAt(loc);
      pt2Node->SetIsVisited();
    }
  }
}

// ---------
// algorithm
// ---------

std::map<locArr, locArr> uniformCost(pfMap &map,
                                     bool visualize = false,
                                     bool animate = false){
  // initializing containers
  std::map<locArr, int> cumCostMap;   // save cumCost for found locations
  std::map<locArr, locArr> history;   // link visited location to predecessor
  // using lamda expression (https://en.cppreference.com/w/cpp/language/lambda):
  auto cheapest = [&cumCostMap](locArr a, locArr b){
    return (cumCostMap.at(a) > cumCostMap.at(b));
  };
  std::priority_queue<locArr,
                      std::vector<locArr>,
                      decltype(cheapest)> unvisitedPQ(cheapest);
  std::array<locArr,4> directions {{{0,1},{1,0},{0,-1},{-1,0}}}; // to loop through neighbors

  // initializing varialbes
  bool targetFound = false;
  locArr startLoc = map.GetStartLoc();
  locArr targetLoc = map.GetTargetLoc();
  locArr currentLoc;
  locArr neighborLoc;
  int neighborCumCost;
  int currentCumCost;
  int iterationCount = 0; // only for ucDebugging!

  // set cumCost for start node, push into PQ
  ucSetCumCost(cumCostMap, startLoc, 0);
  unvisitedPQ.push(startLoc);
  if(animate){map.PrintMap();}
  if(ucDebug){
    std::cout << "DEBUG: start:    " << startLoc[0] << ","
              << startLoc[1] << '\n';
  }

  // central loop (algorithm)
  while(!unvisitedPQ.empty()){
    if(animate){
    // poor man's animation (works though!)
    //ucDrawKnown(map, history); // 'animation'
    map.ReprintMap(); // 'animation'
  }
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    if(visualize || animate){map.GetNodeAt(currentLoc)->SetIsVisited();}
    if (currentLoc == targetLoc){        // end loop if target is found
      if(ucDebug){std::cout << "DEBUG: target reached!" << '\n';}
      targetFound = true;
      break;
    }
    if(ucDebug){
      std::cout << "DEBUG: current:   " << currentLoc[0] << ","
                << currentLoc[1] << '\n';
      iterationCount+=1;
    }

    // check neighbors of current node
    for(auto direction : directions){
      neighborLoc = ucAddLocArr(currentLoc, direction);
      //pfNode* pt2Node = map.GetNodeAt(neighborLoc); // store pointer to neighbor node

      if(ucIsWall(map, neighborLoc) || ucIsKnown(history, neighborLoc))
        continue;

      currentCumCost = ucGetCumCost(cumCostMap, currentLoc);
      neighborCumCost = currentCumCost + map.GetNodeAt(neighborLoc)->GetWeight();

      ucSetCumCost(cumCostMap, neighborLoc, neighborCumCost);
      ucSetHistory(history, neighborLoc, currentLoc);
      if(visualize || animate){map.GetNodeAt(neighborLoc)->Setf(neighborCumCost);}
      unvisitedPQ.push(neighborLoc);
      if(ucDebug){
        std::cout << "DEBUG: neighbor:  " << neighborLoc[0] << ","
                  << neighborLoc[1] << "\n";
      }
    } // end of for loop through neighbors
  } // end of while loop through unvisitedPQ

  // rest only for testing
  if(targetFound){
    if(ucDebug){
      std::cout << "DEBUG: size of history: " << history.size() << '\n';
      std::cout << "DEBUG: iterationCount = " << iterationCount << '\n';
      std::cout << "DEBUG: cumCost of target: "
                << ucGetCumCost(cumCostMap, targetLoc) << '\n';
    }
    if(animate || visualize){ucDrawPath(history, map);}
    if(animate){map.ReprintMap();}
    //std::cout << "Target found!" << '\n';
  }
  else{
    //std::cout << "Target not found! " << '\n';
  }
  return history;
}
