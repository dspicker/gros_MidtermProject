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

/*  NOTES:
**
**  The A* algorithm displays the f = g+h value, due to the limitation of two
**  characters on the printed map this can not be displayed correctly on large
**  maps.
**
**  This program can be uesed on all maps;
**
*/

int main(){

  bool showPathData = false;  // show cost and lengh of path

  // change size of random map if you want
  int hight = 40;
  int width = 40;

  // Use saved maps:
    pfMap compare1(*pfMap::LoadMap("maps/compare1.csv"));
  //pfMap compare1(*pfMap::LoadMap("maps/map1.csv"));
  //pfMap compare1(*pfMap::LoadMap("maps/map2.csv"));

  // Use random generated map with specified dimensions:
  // (be careful not to initiate compare1 twice)

  //pfMap compare1(hight, width);
  if(false){ // toggle if using random maps
  compare1.SetTypeAt(2,2,4);  // set start
  compare1.SetTypeAt(hight-2, width-2, 5);  // set target
}

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
  auto flow = Breadthfirst(compare1BF,visualize, animate);
  if(!animate){compare1BF.PrintMap();}
  if(showPathData){
    std::cout << "length: " << bfDrawPath(flow, compare1BF)[0] << "\n"
              << "cost:   " << bfDrawPath(flow, compare1BF)[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "uniform cost:";
  auto ucHistory = uniformCost(compare1UC,visualize, animate);
  if(!animate){compare1UC.PrintMap();}
  if(showPathData){
    std::cout << "length: " << ucDrawPath(ucHistory, compare1UC)[0] << "\n"
              << "cost:   " << ucDrawPath(ucHistory, compare1UC)[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "greedy best first:";
  auto gbHistory = GreedyBestFirst(compare1GB, visualize, animate);
  if(!animate){compare1GB.PrintMap();}
  if(showPathData){
    std::cout << "length: " << gbDrawPath(gbHistory, compare1GB)[0] << "\n"
              << "cost:   " << gbDrawPath(gbHistory, compare1GB)[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "A* (manhattan):";
  pfAStar ASMan(compare1ASMan);
  ASMan.solve("Manhattan",visualize, animate);
  if(!animate){compare1ASMan.PrintMap();}
  if(showPathData){
    std::cout << "length: " << ASMan.UpdateMap()[0] << "\n"
              << "cost:   " << ASMan.UpdateMap()[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "A* (euklid):";
  pfAStar ASEuk(compare1ASEuk);
  ASEuk.solve("Euklid",visualize, animate);
  if(!animate){compare1ASEuk.PrintMap();}
  if(showPathData){
    std::cout << "length: " << ASEuk.UpdateMap()[0] << "\n"
              << "cost:   " << ASEuk.UpdateMap()[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "A* (minimum):";
  pfAStar ASMin(compare1ASMin);
  ASMin.solve("Minimum",visualize, animate);
  if(!animate){compare1ASMin.PrintMap();}
  if(showPathData){
    std::cout << "length: " << ASMin.UpdateMap()[0] << "\n"
              << "cost:   " << ASMin.UpdateMap()[1]
              << '\n'
              << '\n';
  }

  enterToContinue();

  std::cout << "A* (supremum):";
  pfAStar ASSup(compare1ASSup);
  ASSup.solve("Supremum",visualize, animate);
  if(!animate){compare1ASSup.PrintMap();}
  if(showPathData){
    std::cout << "length: " << ASSup.UpdateMap()[0] << "\n"
              << "cost:   " << ASSup.UpdateMap()[1]
              << '\n'
              << '\n';
  }
  return 0;
}
