#include "class_ANode.h"
#include <iostream>


int main(){


  ANode node(3);

  node.Setg(22.22);
  
  std::cout << ">>>Node Weight: " << node.GetWeight() << std::endl;
  std::cout << ">>>Node g: " << node.Getg() << std::endl;
  
  
  return 0;
}
