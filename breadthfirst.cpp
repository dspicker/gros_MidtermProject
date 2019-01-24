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

// forward definition to use for animation:
void bfDrawPath(std::map< bfLocation , bfLocation > flow, pfMap &Map);

// main algorithm
std::map< bfLocation , bfLocation > Breadthfirst(pfMap &Map, bool animate=false){
  std::queue< bfLocation > search_queue ;           // the queue of the algorithm
  // get target node from map. this algorithm starts at the target
  bfLocation search_begin = Map.GetTargetLoc() ;
  // put coordinates of starting-point into queue
  search_queue.push(search_begin) ;

  bfLocation goal = Map.GetStartLoc();

  // the map that is later returned.
  // it stores, from which neighbour of the first argument (key) the algorithm came from
  std::map< bfLocation , bfLocation > search_result ;

  if(animate){Map.PrintMap();}
  // actual algorithm
  while ( !search_queue.empty() ) {
    // take an element out of the queue
    bfLocation current = search_queue.front();
    search_queue.pop();
    if(animate){
      Map.GetNodeAt(current)->SetIsVisited();
      Map.ReprintMap();
    }

    // early exit as soon as start node is reached.
    if( current == goal ) break ;

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
  if(animate){
    bfDrawPath(search_result, Map);
    Map.ReprintMap();
  }

  return search_result;
}

// modifies the map to draw the resulting path. call only after Breadthfirst
void bfDrawPath(std::map< bfLocation , bfLocation > flow, pfMap &Map){
  bfLocation start = Map.GetStartLoc() ;
  bfLocation target = Map.GetTargetLoc() ;

  if( flow.find(start) == flow.end() ){
    std::cout << "Breadthfirst: No Path found!" << '\n';
    return ;
  }

  bfLocation next = flow[start] ;
    //for(int i=0; i<20 ; i++) {
    while ( next != target ) {
      //Map.SetTypeAt(next[0],next[1],6);
      Map.GetNodeAt(next)->SetIsPath();
      next = flow[next];
  }
}
