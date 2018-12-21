#include "class_node.h"

#include <iostream>
#include <array>

pfNode::pfNode(int t){
  // TODO: catch wrong values of t .
  type = t;
  switch (type) {
    case 1 :         // Wall
      weight = -1 ;
      break;
    case 2 :        // Grass
      weight = 1 ;
      break;
    case 3 :        // Forest
      weight = 5 ;
      break;
    default :
      weight = 1 ;
  }

}

std::string pfNode::GetTypeName(){
  switch (type) {
    case 1 :         // Wall
      return "Wall" ;
    case 2 :        // Grass
      return "Grass" ;
    case 3 :        // Forest
      return "Forest" ;
    default :
      return "Undefined" ;
  }

}

void pfNode::Print(){
  std::array<int,3> color = {0,0,0};
  switch (type) {
    case 1 :         // Wall
      color = {180,180,180};
      break;
    case 2 :        // Grass
      color = {51, 204, 51};
      break;
    case 3 :        // Forest
      color = {0, 153, 51};
      break;
  }
  char buffer1[50];
  sprintf(buffer1, "\033[48;2;%u;%u;%um  \033[0m", color[0],color[1],color[2]);
  std::cout << buffer1 ;
}
