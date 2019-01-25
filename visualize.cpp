#include <iostream>
#include <stdlib.h>
#include <limits>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"
#include "greedyBestFirst.cpp"
#include "class_AStar.h"

void enterToContinue(){
  std::cout << "press ENTER to continue" << '\n';
  std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

int main(){
  pfMap compare1(*pfMap::LoadMap("maps/compare1.csv"));

  // copy maps for all algorithms
  pfMap compare1BF(compare1);
  pfMap compare1UC(compare1);
  pfMap compare1GB(compare1);
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
  std::cout << std::endl;
  if(input == "yes")
    animate = true;
  else if(input=="no")
    visualize = true;
  else
    return 1;

  // because the first one doesn't do anything..
  std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');

  std::cout << "breadthfirst:";
  Breadthfirst(compare1BF,visualize, animate);
  if(!animate){compare1BF.PrintMap();}

  enterToContinue();

  std::cout << "uniform cost:";
  uniformCost(compare1UC,visualize, animate);
  if(!animate){compare1UC.PrintMap();}

  enterToContinue();

  std::cout << "greedy best first:";
  GreedyBestFirst(compare1GB, visualize, animate);
  if(!animate){compare1GB.PrintMap();}

  enterToContinue();

  std::cout << "A* (manhattan):";
  pfAStar ASMan(compare1ASMan);
  ASMan.solve("Manhattan",visualize, animate);
  if(!animate){compare1ASMan.PrintMap();}

  enterToContinue();

  std::cout << "A* (euklid):";
  pfAStar ASEuk(compare1ASEuk);
  ASEuk.solve("Euklid",visualize, animate);
  if(!animate){compare1ASEuk.PrintMap();}

  enterToContinue();

  std::cout << "A* (minimum):";
  pfAStar ASMin(compare1ASMin);
  ASMin.solve("Minimum",visualize, animate);
  if(!animate){compare1ASMin.PrintMap();}

  enterToContinue();

  std::cout << "A* (supremum):";
  pfAStar ASSup(compare1ASSup);
  ASSup.solve("Supremum",visualize, animate);
  if(!animate){compare1ASSup.PrintMap();}

  return 0;
}
