#ifndef pfAStar_h
#define pfAStar_h


#include "class_node.h"
#include "class_map.h"
#include <map>
#include <array>


class pfAStar {

 private:
  const pfMap map;
  const std::array<int,2> StartCoord;
  const std::array<int,2> TargetCoord;

  openlist;
  closedlist;
  
 public:

  //Constructors
 pfAStar(pfMap _map, std::array<int,2> _start, std::array<int,2> _target)
   : map, StartCoord, TargetCoord {
  }
  
   //Functions:

   //Heuristic:
   double h( std::array<int,2> ) {


 }
  








}
