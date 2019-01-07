#include <iostream>
#include <queue>

#include "class_map.h"

struct bf_node {
  std::array<int,2> cur_node;
  int distance;
  std::array<int,2> came_from;
};


std::map< std::array<int,2> , std::array<int,2> > Breadthfirst(pfMap Map){
  std::queue< std::array<int,2> > search_queue ;
  std::array<int,2> search_begin = Map.GetTargetLoc() ;
  search_queue.push(search_begin) ;

  std::map< std::array<int,2> , std::array<int,2> > search_result ;


}
