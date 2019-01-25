#include <iostream>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"
#include "class_AStar.h"

int main(){
  pfMap compare1(*pfMap::LoadMap("maps/map1.csv"));

  // copy maps for all algorithms
  pfMap compare1BF(compare1);
  pfMap compare1UC(compare1);
  pfMap compare1ASMan(compare1);
  pfMap compare1ASEuk(compare1);
  pfMap compare1ASMin(compare1);
  pfMap compare1ASSup(compare1);

  std::cout << "breadthfirst:" << '\n';
  Breadthfirst(compare1BF,1);
  compare1BF.PrintMap();

  std::cout << "uniform cost" << '\n';
  uniformCost(compare1UC,1);
  compare1UC.PrintMap();

  std::cout << "A* (manhattan)";
  pfAStar ASMan(compare1ASMan);
  ASMan.solve("Manhattan",1);
  compare1ASMan.PrintMap();


  std::cout << "A* (euklid)";
  pfAStar ASEuk(compare1ASEuk);
  ASEuk.solve("Euklid",1);
  compare1ASEuk.PrintMap();


  std::cout << "A* (minimum)";
  pfAStar ASMin(compare1ASMin);
  ASMin.solve("Minimum",1);
  compare1ASMin.PrintMap();


  std::cout << "A* (supremum)";
  pfAStar ASSup(compare1ASSup);
  ASSup.solve("Supremum",1);
  compare1ASSup.PrintMap();






}
