#include <iostream>
#include "class_AStar.h"
#include "class_map.h"

int main(){

  
  pfMap map1(60,20);
  map1.GetNodeAt(1,10)->SetStart();
  map1.GetNodeAt(55,10)->SetTarget();
 
    //pfMap map1(*pfMap::LoadMap("./maps/map1.csv"));

  pfMap map2(map1);
  pfMap map3(map1);
  pfMap map4(map1);
  
  pfAStar star1(map1);
  pfAStar star2(map2);
  pfAStar star3(map3);
  pfAStar star4(map4);

  
  star4.solve("Minimum");
  star4.UpdateMap("h");
  std::cout << "MINIMUM:" << std::endl; 
  map4.PrintMap();

  star1.solve("Supremum");
  star1.UpdateMap("f");
  std::cout << "SUPREMUM:" << std::endl; 
  map1.PrintMap();
  
  star2.solve("Manhattan");
  star2.UpdateMap("g");
  std::cout << "MANHATTEN:" << std::endl; 
  map2.PrintMap();
  
  star3.solve("Euklid");
  star3.UpdateMap();
  std::cout << "EUKLID:" << std::endl; 
  map3.PrintMap();
}
