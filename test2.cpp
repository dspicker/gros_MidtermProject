#include <iostream>
#include <array>

#include "class_map.h"
#include "class_node.h"
#include "class_asNode.h"
#include "class_AStar.h"

int main(){

  
  std::array<int,2> position = {1,2};


  pfNode a(1);

  asNode b(position, &a);

  std::cout << b.GetType() << ", " << *b.isVisited() << std::endl
	    << "-------------------------------------"
	    << std::endl;

  
  pfMap map(50,40);
  map.GetNodeAt(1,1)->SetStart();
  map.GetNodeAt(48,38)->SetTarget();
  
  pfAStar star(map);


  /*
  auto vec = star.GetNodes();
  
  
  for(auto it : vec){
    
    std::cout << it.GetPosition()[0] << "|"
	      << it.GetPosition()[1] << " "
	      << it.GetTypeName() << "\t";
    
    std::cout << ">>> NeighborsN:" <<  it.GetNeighbours()->size() ;

    auto vecn = it.GetNeighbours();
    for(auto it2 : *vecn){

      std::cout << " <"
		<< it2->GetPosition()[0] << "|"
		<< it2->GetPosition()[1] << ">;" ;
    }
    std::cout << std::endl;
  }



  std::cout << "g=" << *vec[0].Getf() << std::endl
	    << "Set g = 2" << std::endl;

  vec[0].Setg(2);

  std::cout << "f=" << *vec[0].Getf() << std::endl;
	  
  vec[1].Setg(1);

  star.openList.push(&(vec[0]));
  star.openList.push(&(vec[1]));

  while(!star.openList.empty()){
    
    std::cout << star.openList.top()->GetPosition()[0] << "|"
	      << star.openList.top()->GetPosition()[1] << " "
	      << "f=" << *star.openList.top()->Getg() << std::endl;
    star.openList.pop();
  }

  
  star.openList.push(&(vec[0]));
  star.openList.push(&(vec[1]));

  vec[0].Setg(3);


  while(!star.openList.empty()){
    
    std::cout << star.openList.top()->GetPosition()[0] << "|"
	      << star.openList.top()->GetPosition()[1] << " "
	      << "f=" << *star.openList.top()->Getg() << std::endl;
    star.openList.pop();
  }
  

  
  std::cout << std::endl << "#########################################" << std::endl << std::endl;

  std::cout << "Start? " <<  map.GetNodeAt(vec[star.GetStartIndex()].GetPosition()[0], vec[star.GetStartIndex()].GetPosition()[1] )->GetTypeName() << std::endl;

*/
  
  map.PrintMap();
  star.solve("Pythagoras");
  star.UpdateMap();
  map.PrintMap();

  
}
