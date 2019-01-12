#include "class_map.h"
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>

typedef std::array<int,2> locArr;
bool debug = false;  // display test output at different stages of algorithm

/*  definitions/abbriviations:
    - cumCost: cumulative cost to reach location (includes own weigt)
    -
*/

/* some thoughts regarding the class pfNodes:
A variable 'int cumCost' of pfNode would be usefull to boost performance of
uniformCost by reducing usage of slow std::maps to store cumCost
AND
to make use of a single comparison between already assigned cumCost and
newly calculated cumCost (by starting with cumCost=INT_MAX and just checking if
calculated is smaller than assigned).
*/

/* TODO
    - check if path is as expected..!
    - check border cases
      - target not reachable
    - add functionality to messure time taken to find the targetLoc
    - add function to pfMap class to set start and target locations ALSO
      in the varialbes start_loc and target_loc of pfMap
      (otherwise it is impossible to set them..)
    - test with small random maps! (especially case with no path)
    - use 2D array 'cumCostArr' instead of cumCostMap for better performance?
      (using library arrays, initializing every location with INT_MAX)
*/

// helper functions
bool wasVisited(std::map<locArr, locArr> myHistory, locArr loc){
  return myHistory.count(loc);
}
bool isKnown(std::map<locArr, int> &myCumCostMap, locArr loc){
  return myCumCostMap.count(loc);
}
bool isWall(pfMap map, locArr loc){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}
void setHistory(std::map<locArr, locArr> &myHistory, locArr neighbor, locArr current){
  myHistory[neighbor] = current;
}
void setCumCost(std::map<locArr, int> &myCumCostMap, locArr loc, int cost){
  // change to only set cumCost, if there is no (lower) value saved already??
  myCumCostMap[loc] = cost;
}
int  getCumCost(std::map<locArr, int> &myCumCostMap, locArr loc){
  return myCumCostMap.at(loc);
}
locArr addLocArr(locArr &a, locArr &b){
  locArr res;
  res[0] = a[0] + b[0];
  res[1] = a[1] + b[1];
  return res;
}
void drawPath(pfMap &map, std::map<locArr, locArr> &myHistory){
  locArr targetLoc = map.GetTargetLoc();
  locArr startLoc  = map.GetStartLoc();
  locArr currentLoc = targetLoc;
  locArr previousLoc;
  // loop through linked locations starting at target location
  while(true){
    previousLoc = myHistory.at(currentLoc);
    if(debug){
      std::cout << "DEBUG (drawPath): currentLoc:  " << currentLoc[0] << "," << currentLoc[1] << '\n';
      std::cout << "DEBUG (drawPath): previousLoc: " << previousLoc[0] << "," << previousLoc[1] << '\n';
      std::cout << std::endl;
    }
    if(previousLoc == startLoc)
      break;
    map.GetNodeAt(previousLoc)->SetPath();
    currentLoc = previousLoc;
  }
  map.PrintMap();
}
void drawKnown(pfMap &map, std::map<locArr, locArr> &myHistory){
  locArr startLoc  = map.GetStartLoc();
  locArr targetLoc = map.GetTargetLoc();
  for(auto const &it : myHistory){
    locArr loc = it.first;
    if(loc != startLoc & loc != targetLoc){  // ignore start and target locations
      if(map.GetNodeAt(loc)->GetType() == 2){
        map.SetTypeAt(loc[0], loc[1], 7);
      }
      if(map.GetNodeAt(loc)->GetType() == 3){
        map.SetTypeAt(loc[0], loc[1], 8);
      }
    }
  }
  map.PrintMap();
}

//algorithm
pfMap* uniformCost(pfMap &map){
  map.PrintMap(); // temporary!

  // initializing containers
  std::map<locArr, int> cumCostMap;
  std::map<locArr, locArr> history;   // link visited location to predecessor
  // using lamda expression: https://en.cppreference.com/w/cpp/language/lambda
  auto cheapest = [&cumCostMap](locArr a, locArr b){
    /* (on unweighted map):
    using '>' : similar to breadthfirst algorithm (slow, optimal path)
    using '<' : similar to depthfirst algorithm (fast, suboptimal path)
    */
    return (cumCostMap.at(a) > cumCostMap.at(b));
  };
  std::priority_queue<locArr, std::vector<locArr>, decltype(cheapest)> unvisitedPQ(cheapest);
  std::array<locArr,4> directions {{{0,1},{1,0},{0,-1},{-1,0}}}; // to loop through neigbors

  // initializing varialbes
  bool targetFound = false;
  locArr startLoc = map.GetStartLoc();
  locArr targetLoc = map.GetTargetLoc();
  locArr currentLoc;
  locArr neighborLoc;
  int neighborCumCost;
  int currentCumCost;
  int iterationCount = 0; // only for debugging!

  // set cumCost for start node, push into PQ
  setCumCost(cumCostMap, startLoc, 0);
  unvisitedPQ.push(startLoc);
  if (debug){std::cout << "DEBUG: start:    " << startLoc[0] << "," << startLoc[1] << '\n';}

  // central loop (algorithm)
  while(!unvisitedPQ.empty()){
    // drawKnown(map, history); // poor man's animation (works though!)
    iterationCount+=1;
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    if (currentLoc == targetLoc){        // end loop if target is found
      if(debug){std::cout << "DEBUG: target reached!" << '\n';}
      targetFound = true;
      break;
    }

    if(debug){std::cout << "DEBUG: current:   " << currentLoc[0] << "," << currentLoc[1] << '\n';}

    // check neigbors of current node
    for(auto direction : directions){
      neighborLoc = addLocArr(currentLoc, direction);
      if(isWall(map, neighborLoc) | isKnown(cumCostMap, neighborLoc))
        continue;

      currentCumCost = getCumCost(cumCostMap, currentLoc);
      neighborCumCost = currentCumCost + map.GetNodeAt(neighborLoc)->GetWeight();

      setCumCost(cumCostMap, neighborLoc, neighborCumCost);
      setHistory(history, neighborLoc, currentLoc);

      unvisitedPQ.push(neighborLoc);
      if(debug){std::cout << "DEBUG: neighbor:  " << neighborLoc[0] << "," << neighborLoc[1] << "\n";}
    } // end of for loop through neighbors
  } // end of while loop through unvisitedPQ

  // rest mainly for testing:
  if(targetFound){
    if(debug){
      std::cout << "DEBUG: nodes known  : " << history.size() << '\n';
      std::cout << "DEBUG: iterationCount = " << iterationCount << '\n';
      std::cout << "DEBUG: cumCost of target: " << getCumCost(cumCostMap, targetLoc) << '\n';
      drawKnown(map, history);
    }
    drawPath(map, history);
    drawKnown(map, history);
  }
  else
    std::cout << "target not reachable! " << '\n';

  return &map;
}
