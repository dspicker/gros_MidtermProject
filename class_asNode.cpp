#include "class_asNode.h"
#include <iostream>

void asNode::Setg(double _g){
  g= _g;
}


void asNode::Seth(double _h){
  h= _h;
}

void asNode::Setf(){
  f= g+h;
}

void asNode::SetParent(asNode &(_parent)){
  Parent= &_parent;
}

void asNode::SetNeighbor(asNode &_neighbor){
  Neighbors.push_back(&(_neighbor));
}

void asNode::SetVisited(){
  Visited = true;
}
