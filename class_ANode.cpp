#include "class_ANode.h"
#include <iostream>

void ANode::Setg(double _g){
  g= _g;
}



void ANode::Seth(double _h){
  h= _h;
}

void ANode::Setf(double _f){
  f= _f;
}

void ANode::SetParent(ANode *(_parent)){
  Parent= _parent;
}
