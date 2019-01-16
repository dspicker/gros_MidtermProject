#include "class_AStar.h"

#include "class_node.h"
#include "class_map.h"
#include "class_ANode.h"

#include <map>
#include <array>
#include <math.h>
#include <algorithm>

//Constructors
pfAStar::pfAStar(pfMap &_map){
  SetNodes(_map);  
};


void pfAStar::SetNodes(pfMap &map){

  // Set 'true' for debugging massages
  bool debug = 0; 
  
  asLocation coord;

  
  // Copy map into allNodes
  allNodes.reserve(map.GetNnodes());
  
  for(int x=0; x<map.GetWidth(); x++){
    for(int y=0; y<map.GetHeight(); y++){
      coord = {x,y};
      allNodes.push_back(ANode(coord, map.GetNodeAt(x,y)));

      // Set Index of Start Node
      if(map.GetNodeAt(x,y)->GetType() == 4)
	START_INDEX = x*map.GetHeight() + y;
 
      // Set Index of Finish Node
      else if(map.GetNodeAt(x,y)->GetType() == 5)
	FINISH_INDEX = x*map.GetHeight() + y;
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

      // pos+(1,0)
      size_t n = i + map.GetHeight();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( (allNodes[n]) );

      // pos+(-1,0)
      n = i - map.GetHeight();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( (allNodes[n]) );

      // pos+(0,1)
      n = i+1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( (allNodes[n]) );

      // pos+(0,-1)
      n = i-1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbour( (allNodes[n]) );
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
	    allNodes[i].SetNeighbour(allNodes[j]);
	  }
	}
	if(debug)
	  std::cout << std::endl;
      
      }    
    } 
  }
}



//Heuristic:
double pfAStar::Pythagoras( asLocation &Pos){
  return sqrt(pow(Pos[0],2) + pow(Pos[1],2));
}

double pfAStar::Manhatten( asLocation &Pos){
  return Pos[0] + Pos[1];
}



void pfAStar::solve(std::string HeuristicName){
  
  // Set chosen Heuristic
  typedef double (pfAStar::*Fptr_heuristic_double)(asLocation &Pos);
  Fptr_heuristic_double HEURISTIC_PTR;
 
  if     (HeuristicName == "Pythagoras")
    HEURISTIC_PTR = &pfAStar::Pythagoras;
  
  else if(HeuristicName == "Manhatten")
    HEURISTIC_PTR = &pfAStar::Manhatten;
  
  else{ // If User gives unknown Heuristic, it ends the function 
    std::cout << ">>> ERROR: '" << HeuristicName << "' is no known Heuristic!" << std::endl;
    return; 
  }

  
  // Set Start Node
  ANode *actualNode = &(allNodes[START_INDEX]);
  actualNode->Setg(0);
  actualNode->Seth( Pythagoras( *(actualNode->GetPositionRef()) ) );

  // Set Neighbours of Start Node
  std::vector<ANode*> *actualNeighbours = actualNode->GetNeighbours();

  // Fill openList with Start Node
  openList.push(actualNode);
  closedList.push_back(&allNodes[FINISH_INDEX]);
  
	    	    
  while( !openList.empty() ){

    if(std::binary_search(closedList.begin(), closedList.end(), actualNode)) continue; 
    
    for(auto it : *actualNeighbours){

      // If Node was not visited before, set Parameters for the 1st time
      if(!*it->isVisited()){
	it->Seth( Pythagoras( *(it->GetPositionRef()) ));
	it->Setg( *actualNode->Getg() + it->GetWeight() );
	it->Setf();
	it->SetParent(*actualNode);
	it->SetVisited();
	openList.push(it);
      }
      // If 
      else if(std::find(closedList.begin(), closedList.end(), it) == closedList.end()){
	//else if(!std::binary_search(closedList.begin(), closedList.end(), it)){
      	
	if( *actualNode->Getg() + it->GetWeight() ){
	  it->Setg( *actualNode->Getg() + it->GetWeight() );
	  it->Setf();
	  it->SetParent(*actualNode);
	}

	
      }// else 
    }// for it:*actualNeighbours
    
    closedList.push_back(actualNode);
    //std::sort(closedList.begin(), closedList.end(), compare_asNodes);

    openList.pop();
    actualNode = openList.top();
    actualNeighbours = actualNode->GetNeighbours(); 
    
  }// while


  actualNode=&allNodes[FINISH_INDEX];
  
  while(actualNode->GetType() != 4){

    std::cout << actualNode->GetParent()->GetPosition()[0] << "|"
	      << actualNode->GetParent()->GetPosition()[1] << ">>";

    actualNode=actualNode->GetParent();
      

  }

}

