#include <iostream>
#include "class_AStar.h"
#include "class_map.h"

int main(){


  pfMap map1(60,20);
  map1.GetNodeAt(1,1)->SetStart();
  map1.GetNodeAt(58,18)->SetTarget();

  pfMap map2(map1);
  pfMap map3(map1);
  
  pfAStar star1(map1);
  pfAStar star2(map2);
  pfAStar star3(map3);

  star1.solve("Supremum");
  star1.UpdateMap();
  std::cout << "SUPREMUM:" << std::endl; 
  map1.PrintMap();
  
  star2.solve("Manhatten");
  star2.UpdateMap();
  std::cout << "MANHATTEN:" << std::endl; 
  map2.PrintMap();
  
  star3.solve("Euklid");
  star3.UpdateMap();
  std::cout << "EUKLID:" << std::endl; 
  map3.PrintMap();
}
