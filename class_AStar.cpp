#include "class_AStar.h"

#include "class_node.h"
#include "class_map.h"
#include "class_ANode.h"

#include <map>
#include <array>
#include <math.h>
#include <algorithm>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>

#include <stdlib.h> //exit

//Constructors
pfAStar::pfAStar(pfMap &_map) : MapPtr(&_map){
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
      else if(map.GetNodeAt(x,y)->GetType() == 5){
	FINISH_INDEX = x*map.GetHeight() + y;
	FINISH_COORD[0] = x;
	FINISH_COORD[1] = y; 
      }
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
  return std::abs(Pos[0]-FINISH_COORD[0]) + std::abs(Pos[1]-FINISH_COORD[1]);
}



void pfAStar::solve(std::string HeuristicName){

  // Set DEBUGMOD if(1) for getting Debugging Massages
#define DEBUGMOD if(0)
  
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
  actualNode->Seth( Manhatten( *(actualNode->GetPositionRef()) ) );
  actualNode->Setf();
  actualNode->SetVisited();

  // Set Neighbours of Start Node
  std::vector<ANode*> *actualNeighbours = actualNode->GetNeighbours();

  // Fill openList with Start Node
  openList.push(actualNode);
  closedList.push_back(&allNodes[FINISH_INDEX]);

  bool FINISH_FOUND = false;
  
  while(1){

    if(openList.empty()) break; 
    
    actualNode = openList.top();
    openList.pop();
    closedList.push_back(actualNode);
    actualNeighbours = actualNode->GetNeighbours();
    
    //DEBUGMOD std::this_thread::sleep_for (std::chrono::milliseconds(500));
    
    DEBUGMOD std::cout << std::endl <<  ">>> closedList: ";

    for(auto it : closedList){
      DEBUGMOD std::cout << "(" << it->GetPosition()[0]
			 << "|" << it->GetPosition()[1] << "), ";

    }

    DEBUGMOD std::cout << std::endl;
    
    DEBUGMOD std::cout << actualNode->GetPosition()[0] << "|"
		       << actualNode->GetPosition()[1] << "("
		       << *actualNode->Geth() << ", "
		       << *actualNode->Getg() << ", "
		       << *actualNode->Getf() << ")" 
		       << " : " << std::endl;

    for(auto it : *actualNeighbours){

      DEBUGMOD std::cout << "\t"
			 << "<" << it->GetPosition()[0]
			 << "|" << it->GetPosition()[1] << ">";
	       
   
      // If Node was not visited before, set Parameters for the 1st time
      if(!*it->isVisited()){
	DEBUGMOD std::cout << "N(" ;
	
	it->Seth( Manhatten( *(it->GetPositionRef()) ));
	it->Setg( *actualNode->Getg() + it->GetWeight() );
	it->Setf();
	it->SetParent(*actualNode);
	it->SetVisited();
	openList.push(it);
      }
      else if( *(actualNode->Getg()) + it->GetWeight() < *(it->Getg()) ){
	DEBUGMOD std::cout << "O(";
	
	it->Setg( *(actualNode->Getg()) + it->GetWeight() );
	it->Setf();
	it->SetParent(*actualNode);
      }	
      else
	DEBUGMOD std::cout << " (";

      if( it->GetType() == 5)
	FINISH_FOUND = true;
      
      DEBUGMOD std::cout << *it->Geth() << ", "
			 << *it->Getg() << ", "
			 << *it->Getf() << ")" << std::endl;
      

    }// for it:*actualNeighbours
  }// while

  if(FINISH_FOUND){
    std::cout << ">>>FINISH FOUND!" << std::endl;

    for( actualNode = &allNodes[FINISH_INDEX], std::cout <<  actualNode->GetPosition()[0] << "|" << actualNode->GetPosition()[1];
	 actualNode->GetType() != 4;
	 actualNode=actualNode->GetParent()){

      DEBUGMOD std::cout << " >> "
			 << actualNode->GetParent()->GetPosition()[0] << "|"
			 << actualNode->GetParent()->GetPosition()[1];


      PathNodes.push_back(actualNode);
   
    
    }
    std::cout << std::endl << std::endl;
  }
}




void pfAStar::UpdateMap(){

  for( auto it : PathNodes){

    MapPtr->GetNodeAt( it->GetPosition()[0], it->GetPosition()[1]) -> SetIsPath();

  }
  
}

