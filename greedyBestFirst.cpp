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
  const double p = 1;
  double result = 0;
  if( p>10.0 ){
    result = std::max( fabs(loc1[0]-loc2[0]), fabs(loc1[1]-loc2[1]) );
  } else {
    result =pow( pow( fabs(loc1[0]-loc2[0]), p) + pow( fabs(loc1[1]-loc2[1]), p) , 1/p );
  }
  return result ;
}


// main algorithm
std::map< gbLoc , double > GreedyBestFirst(pfMap &Map){
  std::map< gbLoc , double > result;
  gbQueue search_queue ;

  gbLoc end_loc = Map.GetTargetLoc() ;
  gbLoc begin_loc = Map.GetStartLoc();
  double dist = gbDistance(begin_loc,end_loc) ;
  search_queue.push( std::make_pair(begin_loc, dist) );

  std::cout << "gBF before loop" << '\n';
  while ( !search_queue.empty() ) {
    gbNode curr = search_queue.top() ;
    search_queue.pop() ;

    if( curr.first == end_loc ) {
      std::cout << "last distance: " << curr.second << '\n';
      break ;
    }

    for( gbLoc next : gbSuccessors(curr.first) ){
      dist = gbDistance(next, end_loc) ;
      int w = Map.GetNodeAt(next)->GetWeight() ;
      if( w == -1 ) continue ;
      dist = dist + (w-1) ;
      if( result.find(next) == result.end() ){
        search_queue.push( std::make_pair(next, dist) );
        result.insert( std::make_pair(next, dist) ) ;
      } else {
        if(result[next] > dist ) { result[next] = dist ;  }
      } // end if-else
    } // end for
  } //end while

  return result;
}


void gbDrawPath(std::map< gbLoc , double > dist_to_target, pfMap &Map){
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
