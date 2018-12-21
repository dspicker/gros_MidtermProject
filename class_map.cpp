#include "class_map.h"

#include <iostream>
#include <chrono>
#include <random>


pfMap::pfMap(int w, int h){
  width = w;
  height = h;
  // fill the nodes-vector with random nodes
  // nodes on the edge of the map should be walls

  // obtain a seed, initialize a random number generator and  initialize a uniform distribution
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<int> rnd_type(1,3);


  for(int i=0 ; i<width ; i++){
    for(int j=0 ; j<height ; j++){
      if( i==0 || i==(width-1) || j==0 || j==(height-1) ){
        nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode(1) ) );
      } else {
        nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode( rnd_type(gen) ) ) );
      }
    }
  }

}

int pfMap::PrintMap(){
  std::array<int,2> pos;
  for(int i=0 ; i<width ; i++){
    for(int j=0 ; j<height ; j++){
      pos[0] = i;
      pos[1] = j;
      
    }
  }

}
