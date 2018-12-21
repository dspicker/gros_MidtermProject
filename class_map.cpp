#include "class_map.h"

#include <chrono>
#include <random>


pfMap::pfMap(int w, int h){
  width = w;
  height = h;
// fill the nodes vector with random nodes
// nodes on the edge of the map should be walls

  nodes.push_back( pfNode(1) );
  nodes.push_back( pfNode(2) );
  nodes.push_back( pfNode(3) );

}
