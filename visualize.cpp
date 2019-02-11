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
  std::cout << "press ENTER to continue" << '\n'; // disable for crappy screenrecording?
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

  bool showPathData = true;  // show cost and lengh of path
  int iterationCount = 0;

  // change size of random map if you want
  int hight = 40;
  int width = 40;

  // Use saved maps:
    pfMap compare(*pfMap::LoadMap("maps/compare1.csv"));
  //pfMap compare(*pfMap::LoadMap("maps/map1.csv"));
  //pfMap compare(*pfMap::LoadMap("maps/map2.csv"));
  //pfMap compare(*pfMap::LoadMap("maps/map1_b.csv"));

  // Use random generated map with specified dimensions:
  /* // (be careful not to initiate compare twice)
  pfMap compare(hight, width);
  compare.SetTypeAt(2,2,4);  // set start
  compare.SetTypeAt(hight-2, width-2, 5);  // set target
  */


  // copy maps for all algorithms
  pfMap compareBF(compare);
  pfMap compareUC(compare);
  pfMap compareGB(compare);
  pfMap compareASMan(compare);
  pfMap compareASEuk(compare);
  pfMap compareASMin(compare);
  pfMap compareASSup(compare);

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
  auto flow = Breadthfirst(compareBF,visualize, animate, &iterationCount);
  if(!animate){compareBF.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << bfDrawPath(flow, compareBF)[0] << "\n"
              << "cost:       " << bfDrawPath(flow, compareBF)[1] << "\n"
              << "iterations: " << iterationCount
              << "\n"
              << '\n';
  }
  iterationCount = 0;

  enterToContinue();

  std::cout << "uniform cost:";
  auto ucHistory = uniformCost(compareUC, visualize, animate, &iterationCount);
  if(!animate){compareUC.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << ucDrawPath(ucHistory, compareUC)[0] << "\n"
              << "cost:       " << ucDrawPath(ucHistory, compareUC)[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;

  enterToContinue();

  std::cout << "greedy best first:";
  auto gbHistory = GreedyBestFirst(compareGB, visualize, animate, &iterationCount);
  if(!animate){compareGB.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << gbDrawPath(gbHistory, compareGB)[0] << "\n"
              << "cost:       " << gbDrawPath(gbHistory, compareGB)[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;

  enterToContinue();

  std::cout << "A* (manhattan):";
  pfAStar ASMan(compareASMan);
  ASMan.solve("Manhattan", visualize, animate, &iterationCount);
  if(!animate){compareASMan.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << ASMan.UpdateMap()[0] << "\n"
              << "cost:       " << ASMan.UpdateMap()[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;

  /*  Skip other metrics of AStar

  enterToContinue();

  std::cout << "A* (euklid):";
  pfAStar ASEuk(compareASEuk);
  ASEuk.solve("Euklid", visualize, animate, &iterationCount);
  if(!animate){compareASEuk.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << ASEuk.UpdateMap()[0] << "\n"
              << "cost:       " << ASEuk.UpdateMap()[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;

  enterToContinue();

  std::cout << "A* (minimum):";
  pfAStar ASMin(compareASMin);
  ASMin.solve("Minimum", visualize, animate, &iterationCount);
  if(!animate){compareASMin.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << ASMin.UpdateMap()[0] << "\n"
              << "cost:       " << ASMin.UpdateMap()[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;

  enterToContinue();

  std::cout << "A* (supremum):";
  pfAStar ASSup(compareASSup);
  ASSup.solve("Supremum", visualize, animate, &iterationCount);
  if(!animate){compareASSup.PrintMap();}
  if(showPathData){
    std::cout << "length:     " << ASSup.UpdateMap()[0] << "\n"
              << "cost:       " << ASSup.UpdateMap()[1] << "\n"
              << "iterations: " << iterationCount
              << '\n'
              << '\n';
  }
  iterationCount = 0;
  */
  return 0;
}
