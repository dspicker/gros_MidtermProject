#include "class_map.h"

#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <map>
// #include <climit> // INT_MAX for

typedef std::array<int,2> locArr;

bool debug = true;  // display test output at different stages of algorithm

/* some thoughts regarding the class pfNodes:
A variable 'int cumCost' of pfNode would be usefull to boost performance of
uniformCost by reducing usage of slow std::maps to store cumCost
AND
to make use of a single comparison between already assigned cumCost and
newly calculated cumCost (by starting with cumCost=INT_MAX and just checking if
calculated is smaller than assigned).
*/

/* TODO
    - fix history!
      - Does the setHistory function work as intended? -> not at all
      - Why is it so fucked up?! (see DEBUG (drawPath) ...)
        -> It does not save the history of neigbors, but rather the history of
           unvisitedPQ
           FIX: track neighbors in history (but than i can't be used to checked
           if visited before -> new way to keep track of that is needed..)
           Use map<locArr, array<int,4> nodeInfo {loc[0], loc[1], cumCost, visited(1 or 0)} ??
    - check if path is as expected..!
    - check border cases
      - target not reachable
      - forest maze
    - add functionality to messure time taken to find the targetLoc
    - add function to pfMap class to set start and target locations ALSO
      in the varialbes start_loc and target_loc of pfMap
      (otherwise it is impossible to set them..)
    - test with small random maps! (especially case with no path)
    - optimize time by minimizing use of maps history and cumCostMap
      in loop through neighbors
    - use 2D array 'cumCostArr' instead of cumCostMap for better performance?
      (using library arrays, initializing every location with INT_MAX)
    - introduce boolean varialbe targetFound to handle impossible case ?
*/

// helper functions
bool wasVisited(std::map<locArr, locArr> myHistory, locArr loc){
  return myHistory.count(loc);
}
bool isWall(pfMap map, locArr loc){
  return (map.GetNodeAt(loc)->GetWeight() == -1);
}
void setHistory(std::map<locArr, locArr> &myHistory, locArr current, locArr previous){
  myHistory[current] = previous;
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

  // draw loop through linked locations starting at target location
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
void drawVisited(pfMap &map, std::map<locArr, locArr> &myHistory){
  locArr startLoc  = map.GetStartLoc();
  for(auto const &it : myHistory){
    locArr loc = it.second;
    if(loc != startLoc)
      map.GetNodeAt(loc)->SetPath();
  }
  map.PrintMap();
}

//algorithm
pfMap* uniformCost(pfMap &map){

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
  locArr previousLoc;
  int neighborCumCost;
  int currentCumCost;
  int iterationCount = 0; // only for debugging!

  // set cumCost for start node, push into PQ
  setCumCost(cumCostMap, startLoc, 0);
  unvisitedPQ.push(startLoc);
  if (debug){std::cout << "DEBUG: start:    " << startLoc[0] << "," << startLoc[1] << '\n';}
  previousLoc = startLoc; // handle border case of first iteration where ther is no previousLoc

  // central loop (algorithm)
  while(!unvisitedPQ.empty()){
    currentLoc = unvisitedPQ.top();
    unvisitedPQ.pop();
    if(wasVisited(history, currentLoc)){
      if(debug){iterationCount+=1;}  // check if it skips already visited nodes as intended
      // abourt iteration if already visited (needed here because of duplicates in unvisitedPQ!!)
      continue;
    }
    history[currentLoc] = previousLoc;
    previousLoc = currentLoc;
    if (currentLoc == targetLoc){        // end loop if target is found
      if(debug){std::cout << "DEBUG: target reached!" << '\n';}
      targetFound = true;
      break;
    }

    // check neigbors of current node
    if(debug){std::cout << "DEBUG: current:   " << currentLoc[0] << "," << currentLoc[1] << '\n';}
    for(auto direction : directions){
      neighborLoc = addLocArr(currentLoc, direction);
      if(isWall(map, neighborLoc) | wasVisited(history, neighborLoc))  // reduncandy
        /* reduncandy!:
           remove reduncandy because this is also checked at start of while-loop
           maybe try to check value and handly error if key invalid?

           An alternavive would be to not check wasVisited at all here
           because cumCost wouldn't be updated then anyways..
        */
        continue;
      /* IMPORTANT: make sure NOT to overwrite a smaller cumCost already entered in cumCostMap!!!*/
      currentCumCost = getCumCost(cumCostMap, currentLoc);
      neighborCumCost = currentCumCost + map.GetNodeAt(neighborLoc)->GetWeight();

      // This is not optimal ATM (works though..)
      if( !cumCostMap.count(neighborLoc)){
        setCumCost(cumCostMap, neighborLoc, neighborCumCost); // <- does not work as intended!
        unvisitedPQ.push(neighborLoc);
      }
      else if(getCumCost(cumCostMap,neighborLoc) > neighborCumCost){
        setCumCost(cumCostMap, neighborLoc, neighborCumCost); // <- does not work as intended!
        unvisitedPQ.push(neighborLoc);
      }
      if(debug){std::cout << "DEBUG: neighbor:  " << neighborLoc[0] << "," << neighborLoc[1] << "\n";}
    } // end of for loop through neighbors

  } // end of while loop through unvisitedPQ

  if(!targetFound){
    if(debug){std::cout << "DEBUG: target not reachable!: " << '\n';}
  }
  if(debug & targetFound){std::cout << "DEBUG: cumCost of target: " << getCumCost(cumCostMap, targetLoc) << '\n';}
  drawPath(map, history);

  if(debug){
    std::cout << "DEBUG: nodes visited: " << history.size() << '\n';
    std::cout << "DEBUG: iterationCount = " << iterationCount << '\n';


    drawVisited(map, history);
  }
  drawVisited(map, history);
  //map.PrintMap();
  return &map;
}
