#include <iostream>
#include <array>

#include "class_map.h"
#include "class_node.h"
#include "class_ANode.h"
#include "class_AStar.h"

int main(){


  pfMap map(60,10);
  map.GetNodeAt(1,1)->SetStart();
  map.GetNodeAt(58,8)->SetTarget();
  
  pfAStar star1(map);
  pfAStar star2(map);
  pfAStar star3(map);

  star1.solve("Supremum");
  star1.UpdateMap();
  std::cout << "SUPREMUM:" << std::endl; 
  map.PrintMap();
  map.ResetMap();

  
  star2.solve("Manhatten");
  star2.UpdateMap();
  std::cout << "MANHATTEN:" << std::endl; 
  map.PrintMap();
  map.ResetMap();

  star3.solve("Euklid");
  star3.UpdateMap();
  std::cout << "EUKLID:" << std::endl; 
  map.PrintMap();

  
  
}
