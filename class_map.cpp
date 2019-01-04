#include "class_map.h"

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>

// default constructor
pfMap::pfMap(){ }

// constructor to initialise the map with random nodes
pfMap::pfMap(int w, int h){
  width = w;
  height = h;
  // fill the nodes-vector with random nodes
  // nodes on the edge of the map should be walls

  // obtain a seed, initialize a random number generator and  initialize a uniform distribution
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937_64 gen(seed);
  std::uniform_int_distribution<int> random(1,4);

  for(int i=0 ; i<width ; i++){
    for(int j=0 ; j<height ; j++){
      if( i==0 || i==(width-1) || j==0 || j==(height-1) ){
        nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode(1) ) );
      } else {
        int rnd_type = random(gen) ;
        if(rnd_type == 4 ){ rnd_type = 2; }
        nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode(rnd_type) ) );
      }
    }
  }
}


// copy constructor
pfMap::pfMap(pfMap &old){
  width = old.width ;
  height = old.height;

  nodes = std::map< std::array<int,2>, pfNode >(old.nodes) ;
  // this is copy constructor of std::map
}

int pfMap::PrintMap(){
  std::array<int,2> pos;
  for(int i=0 ; i<width ; i++){
    for(int j=0 ; j<height ; j++){
      pos[0] = i;
      pos[1] = j;
      auto it = nodes.find(pos);
      if( it != nodes.end() ){
        it->second.Print();
      }
    }
    std::cout << std::endl ;
  }
  std::cout << std::endl ;
}

pfNode* pfMap::GetNodeAt(int x, int y){
  std::array<int,2> pos = {x,y};
  auto it = nodes.find(pos);
  if( it != nodes.end() ){
    return &(it->second) ;
  } else {
    std::cerr << "\033[38;2;255;0;0m"<< "Error in GetNodeAt: Node not found!" << "\033[0m" << std::endl ;
    return NULL;
  }
}

// loads a map from a csv-file. creates new map object and returns pointer to it.
pfMap* pfMap::LoadMap(std::string filename){
  // check if file is a csv file
  std::string test = ".csv" ;
  if( filename.find(test) == std::string::npos){
    std::cerr << "\033[38;2;255;0;0m"<< "Error in LoadMap: txt file required" << "\033[0m" << std::endl ;
    pfMap* merr = new pfMap() ;
    return merr ;
  }


  std::ifstream file(filename);
  std::string str;
  std::vector<std::string> lines ;
  while (std::getline(file, str))
  {
    str.erase(std::remove(str.begin(), str.end(), ';'), str.end());
    //std::cout << str.substr(1,1) << std::endl ;
    std::string instr = str ;
    lines.push_back(instr) ;
  }
  //std::cout <<  lines[0].size() << std::endl ;
  pfMap* m0 = new pfMap();
  int w = lines[0].size() ;
  int h = lines.size();
  m0->width = w ;
  m0->height = h ;


  for(int i=h-1 ; i>=0 ; i--){   // lines, beginning at last and then backwards
    for(int j=0 ; j<w ; j++){
      int newtype = std::stoi( lines[i].substr(j,1) ) ;
      m0->nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode( newtype ) ) );
    }
  }


  return m0 ;
}
