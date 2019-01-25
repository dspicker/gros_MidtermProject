#include <iostream>
#include <stdlib.h>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"
#include "class_AStar.h"

int main(){
  pfMap compare1(*pfMap::LoadMap("maps/compare1.csv"));

  // copy maps for all algorithms
  pfMap compare1BF(compare1);
  pfMap compare1UC(compare1);
  pfMap compare1ASMan(compare1);
  pfMap compare1ASEuk(compare1);
  pfMap compare1ASMin(compare1);
  pfMap compare1ASSup(compare1);

  bool animate = false;
  bool visualize = false;


  std::cout << "animate?" << '\n';
  std::cout << "(yes/no):";
  std::string input;
  std::cin >> input;
  if(input == "yes")
    animate = true;
  else if(input=="no")
    visualize = true;
  else
    return 1;


  std::cout << "breadthfirst:" << '\n';
  Breadthfirst(compare1BF,visualize, animate);
  if(!animate){compare1BF.PrintMap();}

  std::cout << "uniform cost:" << '\n';
  uniformCost(compare1UC,visualize, animate);
  compare1UC.PrintMap();

  std::cout << "A* (manhattan):";
  pfAStar ASMan(compare1ASMan);
  ASMan.solve("Manhattan",visualize, animate);
  if(!animate){compare1ASMan.PrintMap();}

  std::cout << "A* (euklid):";
  pfAStar ASEuk(compare1ASEuk);
  ASEuk.solve("Euklid",visualize, animate);
  if(!animate){compare1ASEuk.PrintMap();}

  std::cout << "A* (minimum):";
  pfAStar ASMin(compare1ASMin);
  ASMin.solve("Minimum",visualize, animate);
  if(!animate){compare1ASMin.PrintMap();}

  std::cout << "A* (supremum):";
  pfAStar ASSup(compare1ASSup);
  ASSup.solve("Supremum",visualize, animate);
  if(!animate){compare1ASSup.PrintMap();}


  return 0;
}
