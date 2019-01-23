#include "class_AStar.h"

#include "class_node.h"
#include "class_map.h"
#include "class_asNode.h"

#include <map>
#include <array>
#include <math.h>
#include <algorithm>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>


//Constructors
pfAStar::pfAStar(pfMap &_map) : MapPtr(&_map){
  //MapPtr = &_map;
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
      allNodes.push_back(asNode(coord, map.GetNodeAt(x,y)));

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


  // Set Neighbors of allNodes
  // You can choose between two Methods:
  // Option1: if(0) or Option 2: if(1)

  if(1){
    //option 1:

    for(std::size_t i=0; i<allNodes.size(); i++){

      if(allNodes[i].GetType() == 1) continue;

      // pos+(1,0)
      size_t n = i + map.GetHeight();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbor( (allNodes[n]) );

      // pos+(-1,0)
      n = i - map.GetHeight();
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbor( (allNodes[n]) );

      // pos+(0,1)
      n = i+1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbor( (allNodes[n]) );

      // pos+(0,-1)
      n = i-1;
      if(allNodes[n].GetType() != 1) allNodes[i].SetNeighbor( (allNodes[n]) );
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
	      std::cout << ">>> Neighbor found! " ;

	    if(allNodes[j].GetType() == 1) continue; //if Node is 'Wall' -> no connection
	    allNodes[i].SetNeighbor(allNodes[j]);
	  }
	}
	if(debug)
	  std::cout << std::endl;

      }
    }
  }
}



// Heuristics:

double pfAStar::Minimum( asLocation &Pos){
  bool comp = std::abs(Pos[0]-FINISH_COORD[0]) < std::abs(Pos[1]-FINISH_COORD[1]);
  return  comp?  std::abs(Pos[0]-FINISH_COORD[0]) : std::abs(Pos[1]-FINISH_COORD[1]);
}

double pfAStar::Supremum( asLocation &Pos){
  bool comp = std::abs(Pos[0]-FINISH_COORD[0]) > std::abs(Pos[1]-FINISH_COORD[1]);
  return  comp?  std::abs(Pos[0]-FINISH_COORD[0]) : std::abs(Pos[1]-FINISH_COORD[1]);
}

double pfAStar::Manhattan( asLocation &Pos){
  return std::abs(Pos[0]-FINISH_COORD[0]) + std::abs(Pos[1]-FINISH_COORD[1]);
}

double pfAStar::Euklid( asLocation &Pos){
  return sqrt(pow(Pos[0]-FINISH_COORD[0],2) + pow(Pos[1]-FINISH_COORD[1],2));
}



/************************************
 *  This is the actual A*-Algorithm *
 ************************************/

void pfAStar::solve(std::string HeuristicName){

  
  // Set DEBUGMOD if(1) for getting Debugging Massages
#define DEBUGMOD if(0)

  // Set chosen Heuristic via a Function-Pointer
  typedef double (pfAStar::*Fptr_heuristic_double)(asLocation &Pos);
  Fptr_heuristic_double HEURISTIC_PTR;

  if      (HeuristicName == "Minimum")   HEURISTIC_PTR = &pfAStar::Minimum;
  else if (HeuristicName == "Supremum")  HEURISTIC_PTR = &pfAStar::Supremum;
  else if (HeuristicName == "Euklid")    HEURISTIC_PTR = &pfAStar::Euklid;
  else if (HeuristicName == "Manhattan") HEURISTIC_PTR = &pfAStar::Manhattan;

  else{ // If User gives unknown Heuristic, it ends the function
    std::cout << ">>> ERROR: '" << HeuristicName << "' is no known Heuristic!" << std::endl;
    return;
  }


  // Set Start Node
  asNode *currentNode = &(allNodes[START_INDEX]);
  currentNode->Setg(0);
  currentNode->Seth( (this->* HEURISTIC_PTR)( *currentNode->GetPositionRef() ) );
  currentNode->Setf();
  currentNode->SetVisited();

  // Set Neighbors of Start Node
  std::vector<asNode*> *currentNeighbors = currentNode->GetNeighbors();

  // Fill openList with Start Node
  openList.push(currentNode);

  bool FINISH_FOUND = false;

  // Start looping over the openList.
  // if openList is empty    => no Path could be found
  // if FINISH_FOUND == true => shortest Path is found
  while(!openList.empty() && !FINISH_FOUND){

    // Set new Node getting viewed
    currentNode = openList.top();

    // Pop it out the List, so it can not get viewed again
    openList.pop();

    // Set Neighbors of currentNode
    currentNeighbors = currentNode->GetNeighbors();


    // DEBUG-CODE
    //DEBUGMOD std::this_thread::sleep_for (std::chrono::milliseconds(500));

    DEBUGMOD std::cout << currentNode->GetPosition()[0] << "|"
		       << currentNode->GetPosition()[1] << "("
		       << *currentNode->Geth() << ", "
		       << *currentNode->Getg() << ", "
		       << *currentNode->Getf() << ")"
		       << " : " << std::endl;

    // Loop over all Neighbors of current Node
    for(auto Neig_It : *currentNeighbors){

      DEBUGMOD std::cout << "\t"
			  << "<" << Neig_It->GetPosition()[0]
			  << "|" << Neig_It->GetPosition()[1] << ">";


      // If Node was not visited before, set Parameters for the 1st time and add it to the openList.
      // This Formulation implements the closedList of the A*-Algorithm indirectly.
      // The advantage is, that the Node does not has to be searched in a List, that scales
      // with the size of the Map.
      // So this implementation should be faster, espacially for big Maps.
      if(!*Neig_It->isVisited()){
	DEBUGMOD std::cout << "N(" ;
	
	Neig_It->Seth( (this->* HEURISTIC_PTR)( *Neig_It->GetPositionRef() ) );
	Neig_It->Setg( *currentNode->Getg() + Neig_It->GetWeight() );
	Neig_It->Setf();
	Neig_It->SetParent(*currentNode);
	Neig_It->SetVisited();
	openList.push(Neig_It);
      }
      // If Node was visited befor, just test, wheather a shorter Path to this Node was found
      // and update it, if it is true.
      else if( *(currentNode->Getg()) + Neig_It->GetWeight() < *(Neig_It->Getg()) ){
	DEBUGMOD std::cout << "O(";

	Neig_It->Setg( *(currentNode->Getg()) + Neig_It->GetWeight() );
	Neig_It->Setf();
	Neig_It->SetParent(*currentNode);
      }
      else
	DEBUGMOD std::cout << " (";

      // Memmorize if Finish is found => Loop breaks
      if( Neig_It->GetType() == 5)
	FINISH_FOUND = true;

      DEBUGMOD std::cout << *Neig_It->Geth() << ", "
			 << *Neig_It->Getg() << ", "
			 << *Neig_It->Getf() << ")" << std::endl;


    }// for Neig_It:*currentNeighbors
  }// while

  
  // If a FinishNodes was reached, Set Path form Finish- to Start-Node.
  if(FINISH_FOUND){
    DEBUGMOD std::cout << ">>>FINISH FOUND!" << std::endl;
    
    // Reserve Space for PathNodes.
    // Smalles Number of PathNodes correspondes to Manhattan Norm
    PathNodes.reserve( Manhattan(*allNodes[START_INDEX].GetPositionRef()) );
    
    for( currentNode = &allNodes[FINISH_INDEX];
	 currentNode->GetType() != 4;
	 currentNode=currentNode->GetParent()){

      //std::cout <<  currentNode->GetPosition()[0] << "|" << currentNode->GetPosition()[1];
      DEBUGMOD {
	std::cout << " >> "
		  << currentNode->GetParent()->GetPosition()[0] << "|"
		  << currentNode->GetParent()->GetPosition()[1];
      }//DEBUGMOD

      PathNodes.push_back(currentNode);
    }
    std::cout << std::endl << std::endl;
  }
}



// Just a Update-Function so the Path can be plotted with the given PrintFunction in pfMap.
void pfAStar::UpdateMap(){

  pfNode* NodePtr;

  for( auto it : allNodes){

    if( *it.isVisited() == true){

      NodePtr = MapPtr->GetNodeAt( it.GetPosition()[0], it.GetPosition()[1]);
      NodePtr->SetIsVisited();
      NodePtr->Setf(*it.Getg());

    }
  }

  for( auto it : PathNodes){
    NodePtr = MapPtr->GetNodeAt( it->GetPosition()[0], it->GetPosition()[1]);
    NodePtr->SetIsPath();
  }

}
