/*  Breadthfirst Algorithm
**  for the Pathfinder Project
**  D.Spicker , Jan 2019
*/

#include <iostream>
#include <queue>
#include <vector>

#include "class_map.h"

typedef std::array<int,2> bfLocation ;

// returns a vector, that is filled with the direct neighbours of the node at the position of id
std::vector< bfLocation > bfNeighbours( bfLocation id ){
  std::vector<bfLocation> result ;

  std::array< bfLocation, 4> directions ;
  directions[0] = {1,0};
  directions[1] = {-1,0};
  directions[2] = {0,1};
  directions[3] = {0,-1};

  for( auto dir : directions){
    bfLocation next = { id[0]+dir[0], id[1]+dir[1] } ;
    result.push_back(next);
  }

  return result;
}

// forward definitions to use for animation:
std::array<int,2> bfDrawPath(std::map< bfLocation , bfLocation > flow, pfMap &Map);
int bfDirection( bfLocation curr, bfLocation next );


// main algorithm
std::map< bfLocation , bfLocation > Breadthfirst(pfMap &Map,
                                                 bool visualize=false,
                                                 bool animate=false,
                                                 int *iterationCount=0){
  std::queue< bfLocation > search_queue ;           // the queue of the algorithm
  // get target node from map. this algorithm starts at the target
  bfLocation search_begin = Map.GetTargetLoc() ;
  // put coordinates of starting-point into queue
  search_queue.push(search_begin) ;
  bool targetFound = false;

  bfLocation goal = Map.GetStartLoc();

  // the map that is later returned.
  // it stores, from which neighbour of the first argument (key) the algorithm came from
  std::map< bfLocation , bfLocation > search_result ;

  if(animate){Map.PrintMap();}
  // actual algorithm
  while ( !search_queue.empty() ) {
    if(iterationCount){*iterationCount+=1;} // do only if iterationCount given as argument
    // take an element out of the queue
    bfLocation current = search_queue.front();
    search_queue.pop();

    if(animate || visualize){
      Map.GetNodeAt(current)->SetIsVisited();
      // set directions to display in terminal
      // (copy-paste from bfDrawPath, could be optimized..)
      for(auto &it : search_result ){
        bfLocation cur = it.first;
        bfLocation nxt = it.second;
        int dir = bfDirection(cur,nxt) ;
        Map.SetDirAt(cur[0],cur[1],dir);
      } // end for loop to mark flow directions
    } // end if(animate || visualize)
    if(animate){Map.ReprintMap();}

    // early exit as soon as start node is reached.
    if( current == goal ){
      targetFound = true;
      break;
    }

    // loop trough all neighbours of current element
    for (bfLocation next : bfNeighbours(current) ) {
      // if the neighbour "next" is not in "search_result" i.e. if "next" has not been visited yet:
      if ( search_result.find(next) == search_result.end() ) {
        // check if neighbour "next" is a wall:
        if( Map.GetNodeAt(next)->GetWeight() != -1 ) {
          //then, put "next" into the queue
          search_queue.push(next);
          // and save from where the algorithm walked to "next"
          search_result[next] = current;
        }
      }
    }
  }
  if(targetFound){
    if(animate || visualize){bfDrawPath(search_result, Map);}
    if(animate){Map.ReprintMap();}
  }
  return search_result;
}

// returns in which direction the flow field points to at the current node
int bfDirection( bfLocation curr, bfLocation next ){
  int dx = next[0] - curr[0] ;
  int dy = next[1] - curr[1] ;

  if( dy == 0){
    if(dx > 0) return 1 ;
    if(dx < 0) return 3 ;
    return 0;
  }
  else if( dx == 0 ){
    if(dy > 0) return 2 ;
    if(dy < 0) return 4 ;
    return 0;
  }
  else {
    return 0 ;
  }

}

// modifies the map to draw the resulting path. call only after Breadthfirst
std::array<int,2> bfDrawPath(std::map< bfLocation , bfLocation > flow, pfMap &Map){
  bfLocation start = Map.GetStartLoc() ;
  bfLocation target = Map.GetTargetLoc() ;
  // initialize return values:
  static std::array<int,2> returnArr;
  returnArr[0] = 0; // lengh of Path
  returnArr[1] = 0; // cost of Path

  if( flow.find(start) == flow.end() ){
    std::cout << "Breadthfirst: No Path found!" << '\n';
    return returnArr;
  }

  bfLocation next = flow[start] ;
    while ( next != target ) {
      returnArr[0] += 1;
      returnArr[1] += Map.GetNodeAt(next)->GetWeight();
      Map.GetNodeAt(next)->SetIsPath();
      next = flow[next];
  } // end while loop

  // set directions to display in terminal
  // (could be implemented into breadthfirst function in visualize/animate sections)
  for(auto &it : flow ){
    bfLocation cur = it.first;
    bfLocation nxt = it.second;
    int dir = bfDirection(cur,nxt) ;
    Map.SetDirAt(cur[0],cur[1],dir);
  } // end for loop to mark flow directions
  return returnArr;
} // end bfDrawPath
