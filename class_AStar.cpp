#include "class_AStar.h"

#include "class_node.h"
#include "class_map.h"


#include <map>
#include <array>



void pfAStar::SetNodes(){

  // Set 'true' for debugging massages
  bool debug = 0; 
  
  typedef std::array<int,2> asLocation ;

  asLocation koord;

  
  // Copy map into allNodes
  allNodes.reserve(map.GetNnodes());
  
  for(int x=0; x<map.GetWidth(); x++){
    for(int y=0; y<map.GetHeigth(); y++){
      koord = {x,y};
      allNodes.push_back(ANode(koord, map.GetNodeAt(x,y)));
    }
  }


        
  std::array< asLocation, 4> DIRECTIONS = {{{ 1, 0},
					    {-1, 0},
					    { 0, 1},
					    { 0,-1}}};

  
  // Set Neighbours of allNodes
  // You can choose between two Methods:
  // Option1: if(0) or Option 2: if(1)
  
  if(1){
    //option 1:

    for(std::size_t i=0; i<allNodes.size(); i++){

      if(allNodes[i].GetType() == 1) continue; 

      size_t n = i + map.GetWidth();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( &(allNodes[n]) );

      n = i - map.GetWidth();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( &(allNodes[n]) );

      n = i+1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( &(allNodes[n]) );

      n = i-1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( &(allNodes[n]) );
    } // for
    
  } else {
    // Option 2:
    
    for(size_t i=0; i<allNodes.size(); i++){
      if(allNodes[i].GetType() == 1) continue;
   
      for(size_t j=0; j<allNodes.size(); j++){

	if(debug)
	  std::cout << "<" << allNodes[i].GetPosition()[0] << "|" << allNodes[i].GetPosition()[1] << "> "
		    << "<"<< allNodes[j].GetPosition()[0] << "|" << allNodes[j].GetPosition()[1] << "> ";
	       	
	for(int i=0; i<4; i++){
	  if(allNodes[j].GetPosition()[0] == allNodes[i].GetPosition()[0] + DIRECTIONS[i][0]
	     && allNodes[j].GetPosition()[1] == allNodes[i].GetPosition()[1] + DIRECTIONS[i][1]){

	    if(debug)
	      std::cout << ">>> Neighbour found! " ;
	  
	    if(allNodes[j].GetType() == 1) continue; //if Node is 'Wall' -> no connection
	    allNodes[i].SetNeighbour(&(allNodes[j]));
	  }
	}
	if(debug)
	  std::cout << std::endl;
      
      }    
    } 
  }
}
