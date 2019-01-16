#include "class_ANode.h"
#include <iostream>

void ANode::Setg(double _g){
  g= _g;
}


void ANode::Seth(double _h){
  h= _h;
}

void ANode::Setf(){
  f= g+h;
}

void ANode::SetParent(ANode &(_parent)){
  Parent= &_parent;
}

void ANode::SetNeighbour(ANode &_neighbour){
  Neighbours.push_back(&(_neighbour));
}

void ANode::SetVisited(){
  Visited = true;
}
