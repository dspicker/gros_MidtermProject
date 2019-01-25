#include "class_node.h"

#include <iostream>
#include <array>

// constructor
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

void pfNode::SetStart(){
  type = 4;
  weight = 1;
}
void pfNode::SetTarget(){
  type = 5;
  weight = 1;
}
void pfNode::SetPath(){
  type = 6;
}

// additional types to visualize visited/checked nodes (Felix) :
void pfNode::setType(int t){
  type = t;
}
void pfNode::getType(int t){
  type = t;
}

// end of additons (Felix)

void pfNode::SetIsPath(){
  isPath = true;
}

void pfNode::ResetIsPath(){
  isPath = false;
}

void pfNode::SetIsVisited(){
  isVisited = true;
}

void pfNode::ResetIsVisited(){
  isVisited = false;
}

void pfNode::Setf(double _f){
  f = _f;
}

  void pfNode::setDirection(int dir){
    if( dir>=0 && dir<=4 )
      direction = dir ;
  }


std::string pfNode::GetTypeName()const{
  switch (type) {
    case 1 :         // Wall
      return "Wall" ;
    case 2 :        // Grass
      return "Grass" ;
    case 3 :        // Forest
      return "Forest" ;
    case 4 :        // start-node
      return "Start-Node" ;
    case 5 :        // target-node
      return "Target-Node" ;
    case 6 :        // target-node
      return "Path-Node" ;
// additional types to visualize visited/checked nodes (Felix) :
    case 7 :        // visited/checked grass
      return "visited Grass" ;
    case 8 :        // visited/checked forest
      return "visited Forest" ;
    default :
      return "Undefined" ;
// end of additions (Felix)
  }

}

void pfNode::Print(){
  std::array<int,3> color = {0,0,0};
  switch (type) {
    case 1 :         // Wall
      color = {100,100,100};
      break;
    case 2 :        // Grass
      color = {51, 204, 51};
      break;
    case 3 :        // Forest
      color = {0, 153, 51};
      break;
    case 4 :       // start
      color = {204, 51, 0};
      break;
    case 5 :       // target
      color = {0, 51, 204};
      break;
    case 6 :       // target
      color = {255, 51, 204};
      break;
      // additional types. are they obsolete??
    case 7 :      // visited Grass
      color = {101, 204, 101};
      break;
    case 8 :      // visited forest
      color = {50, 153, 101};
      break;
  }  // end switch

  char rep[] = "  " ; //representation of the nodes on the screen.
  if(direction != 0){  // if direction is not default, print it to the screen
    //sprintf(rep," %d ", direction );
    if( direction == 1 ) sprintf(rep," >");
    if( direction == 2 ) sprintf(rep," ^");
    if( direction == 3 ) sprintf(rep," <");
    if( direction == 4 ) sprintf(rep," v");
  }
  if( f != -1){   // if f is not default(-1) it was set and the user probably wants to draw it into the map
    sprintf(rep,"%.2d",(int)f%100); // %100, so that just the last two digits will print
  }

  if(isPath && type!=4 && type!=5){
    color[0] = color[1] + 50;
    color[1] = color[1] + 50;
    color[2] = 0;
  }
  else if(isVisited && type!=4 && type!=5){
    color[0] += 80;
    color[2] += 80;
  }
  char buffer1[50];
  sprintf(buffer1, "\033[48;2;%u;%u;%um%s\033[0m", color[0],color[1],color[2],rep);

  std::cout << buffer1 ;
}
