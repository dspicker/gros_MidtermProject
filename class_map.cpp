#include "class_map.h"

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>

// default constructor
pfMap::pfMap(){ }

// constructor to initialise the map with random weighted nodes
pfMap::pfMap(int w, int h) : pfMap(w,h,1) {}    // delegating ctor

// constructor to initialise the map with random nodes
pfMap::pfMap(int w, int h, bool weighted){
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

	// DEBUG -- No Walls in Map
	if(0){
	  if(rnd_type == 1){
	    j--;
	    continue;
	  }
	}

        if(rnd_type == 4 ){ rnd_type = 2; }
        if( !weighted && rnd_type==3 ){rnd_type=2;}
        nodes.insert( std::make_pair( std::array<int,2>{i,j}, pfNode(rnd_type) ) );
      }
    }
  }

  start_loc[0] = 0;
  start_loc[1] = 0;
  target_loc[0] = 0;
  target_loc[1] = 0;
}

// copy constructor
pfMap::pfMap(pfMap &old){
  width = old.width ;
  height = old.height;

  nodes = std::map< std::array<int,2>, pfNode >(old.nodes) ;
  // this is copy constructor of std::map

  start_loc = old.start_loc;
  target_loc = old.target_loc;
}


void pfMap::SetTypeAt(int x, int y, int t){
  // TODO: check if start and target have already been set.
  if ( x<=0 || y<=0 || x>=width-1 || y>=height-1 ){ return; }
  pfNode* curr = GetNodeAt(x,y) ;
  if ( t==4 ){
    curr->SetStart();
    start_loc[0] = x;
    start_loc[1] = y;
  }
  if( t==5 ) {
    curr->SetTarget();
    target_loc[0] = x;
    target_loc[1] = y;
  }
  if( t==6 ) {
    curr->SetPath();
  }
  // additional types to visualize visited/checked nodes (Felix) :
  if( t==7 || t==8){
    curr->setType(t);
  }
}
// end of additons (Felix)

std::array<int,2> pfMap::GetStartLoc(){
  return start_loc;
}

std::array<int,2> pfMap::GetTargetLoc(){
  std::array<int,2> ret;
  ret[0] = target_loc[0];
  ret[1] = target_loc[1];
  //std::cout << ret[0] << " gettar " << ret[1] << std::endl ;
  return ret;
}


// prints the map to std::cout
void pfMap::PrintMap(){
  std::cout << std::endl;
  std::array<int,2> pos;
  for(int j=height-1 ; j>=0 ; j--){
    printf("%.2d", j);
    for(int i=0 ; i<width ; i++){
      pos[0] = i;
      pos[1] = j;
      nodes.at(pos).Print();
    }
    std::cout << std::endl;
  }
  std::cout << "  ";
  for(int i=0; i<width; i++)
    printf("|%.2d", i);

  std::cout << std::endl << std::endl ;
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
pfNode* pfMap::GetNodeAt(std::array<int,2> pos){
  return &( nodes.at(pos) );
}


// loads a map from a csv-file. creates new map object and returns pointer to it.
pfMap* pfMap::LoadMap(std::string filename){
  // check if file is a csv file
  std::string test = ".csv" ;
  if( filename.find(test) == std::string::npos){
    std::cerr << "\033[38;2;255;0;0m"<< "Error in LoadMap: Wrong file!" << "\033[0m" << std::endl ;
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
  std::reverse(lines.begin(), lines.end() ); // needed for correct insertion of nodes
  //std::cout <<  lines[0].size() << std::endl ;
  pfMap* m0 = new pfMap();
  int w = lines[0].size() ;
  int h = lines.size();
  m0->width = w ;
  m0->height = h ;

  for(int i=0 ; i<h ; i++){   // lines
    for(int j=0 ; j<w ; j++){
      int newtype = std::stoi( lines[i].substr(j,1) ) ;
      m0->nodes.insert( std::make_pair( std::array<int,2>{j,i}, pfNode( newtype ) ) );
      if( newtype==4 ){
        m0->start_loc[0] = j;
        m0->start_loc[1] = i;
      }
      if( newtype==5 ){
        m0->target_loc[0] = j;
        m0->target_loc[1] = i;
      }
    }
  }

  return m0 ;
}

// TODO: kann raus.
void pfMap::ResetMap(){
  for(auto it : nodes){
    it.second.ResetIsVisited();
    it.second.ResetIsPath();
    }
}
