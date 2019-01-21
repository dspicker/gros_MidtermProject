#include <iostream>
#include "class_AStar.h"
#include "class_map.h"

int main(){


  pfMap map(60,20);
  map.GetNodeAt(1,1)->SetStart();
  map.GetNodeAt(58,18)->SetTarget();
  
  pfAStar star1(map);
  pfAStar star2(map);
  pfAStar star3(map);
  
  star2.solve("Manhatten");
  star2.UpdateMap();
  std::cout << "MANHATTEN:" << std::endl; 
  map.PrintMap();
  map.ResetMap();

  star3.solve("Euklid");
  star3.UpdateMap();
  std::cout << "EUKLID:" << std::endl; 
  map.PrintMap();
  map.ResetMap();
  
  star1.solve("Supremum");
  star1.UpdateMap();
  std::cout << "SUPREMUM:" << std::endl; 
  map.PrintMap();
  map.ResetMap();

  
  
}
