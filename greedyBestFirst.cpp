/*  Greedy Best-first Algorithm
**  for the Pathfinder Project
**  D.Spicker , Jan 2019
*/

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

#include "class_map.h"

typedef std::array<int,2> gbLoc ;
typedef std::pair<gbLoc,double> gbNode ;

class gbComp {
public:
  bool operator() (const gbNode &lhs, const gbNode &rhs) const {
    return (lhs.second > rhs.second);
  }
};

typedef std::priority_queue< gbNode , std::vector<gbNode> , gbComp > gbQueue ;

// forward declaration because used in GreedyBestFirst function
void gbDrawPath(std::map<locArr, locArr> &myHistory, pfMap &map);

// returns a vector, that is filled with the direct neighbours of the node at the position of id
std::vector< gbLoc > gbSuccessors( gbLoc id ){
  std::vector<gbLoc> result ;
  std::array< gbLoc, 4> directions ;
  directions[0] = {1,0};
  directions[1] = {-1,0};
  directions[2] = {0,1};
  directions[3] = {0,-1};
  for( auto dir : directions){
    gbLoc next = { id[0]+dir[0], id[1]+dir[1] } ;
    result.push_back(next);
  }
  return result;
}

// returns the distance between loc1 and loc2 according to the p-norm.
double gbDistance( gbLoc loc1, gbLoc loc2){
  // set p to the desired value. 1=manhattan-distance, 2=euclidian-dist, p>10=maximum-metric
  const double p = 2;
  double result = 0;
  if( p>10.0 ){
    result = std::max( fabs(loc1[0]-loc2[0]), fabs(loc1[1]-loc2[1]) );
  } else {
    result =pow( pow( fabs(loc1[0]-loc2[0]), p) + pow( fabs(loc1[1]-loc2[1]), p) , 1/p );
  }
  return result ;
}


// main algorithm
std::map< gbLoc , gbLoc > GreedyBestFirst(pfMap &Map, bool visualize=false, bool animate=false){
  std::map< gbLoc , double > result;
  std::map<gbLoc, gbLoc> history;
  gbQueue search_queue ;
  bool targetFound = false;

  gbLoc end_loc = Map.GetTargetLoc() ;
  gbLoc begin_loc = Map.GetStartLoc();
  double dist = gbDistance(begin_loc,end_loc) ;
  search_queue.push( std::make_pair(begin_loc, dist) );

  if(animate){Map.PrintMap();}
  //std::cout << "gBF before loop" << '\n';
  while ( !search_queue.empty() ) {
    gbNode curr = search_queue.top() ;
    search_queue.pop() ;
    // move below neighbor loop?
    if(animate || visualize){Map.GetNodeAt(curr.first)->SetIsVisited();}
    if(animate){Map.ReprintMap();}

    if( curr.first == end_loc ) {
      //std::cout << "last distance: " << curr.second << '\n';
      targetFound = true;
      break ;
    }

    for( gbLoc next : gbSuccessors(curr.first) ){
      dist = gbDistance(next, end_loc) ;
      int w = Map.GetNodeAt(next)->GetWeight() ;
      if( w == -1 ) continue ;
      //dist = dist + (w-1) ; // take cost into account (can be commented out!)
      //if(animate||visualize){Map.GetNodeAt(next)->Setf(w);} // toggle if needed
      if( result.find(next) == result.end() ){
        search_queue.push( std::make_pair(next, dist) );
        result.insert( std::make_pair(next, dist) ) ;
        history[next] = curr.first;
      } else {
        if(result[next] > dist ) { result[next] = dist ;  }
      } // end if-else
    } // end for
  } //end while

  if(targetFound){
    if(animate||visualize){gbDrawPath(history, Map);}
    if(animate){Map.ReprintMap();}
  }

  return history;
}


// copy of ucDrawPath:

void gbDrawPath(std::map<locArr, locArr> &myHistory, pfMap &map){
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
    if(previousLoc == startLoc)
      break;
    map.GetNodeAt(previousLoc)->SetIsPath();
    currentLoc = previousLoc;
  }
}

/*  redundant
void gbDrawPathOld(std::map< gbLoc , double > dist_to_target, pfMap &Map){
  gbLoc end_loc = Map.GetTargetLoc() ;
  //gbLoc begin_loc = Map.GetStartLoc();

  if( dist_to_target.find(end_loc) == dist_to_target.end() ){
    std::cout << "GreedyBestFirst: No Path found!" << '\n';
    return ;
  }

  for( auto it : dist_to_target ){
    gbLoc loc = it.first ;
    Map.GetNodeAt(loc)->Setf(it.second) ;
    //std::cout << it.second << '\n';
  }

}
*/
