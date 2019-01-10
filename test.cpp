#include "class_ANode.h"
#include <iostream>


int main(){


  ANode node(3);
    
  node.Setg(11.11);
  
  std::cout << ">>>Node Weight: " << node.GetWeight() << std::endl;
  std::cout << ">>>Node g: " << node.Getg() << std::endl;

  
  ANode node2(1);
  node2.Setg(22.22);

  std::cout << ">>>Node2 Weight: " << node2.GetWeight() << std::endl;
  std::cout << ">>>Node2 g: " << node2.Getg() << std::endl;

  
  node2.Setparent(&node);
  std::cout << ">>>Node2P Weight: " << node2.Getparent()->GetWeight() << std::endl;
  std::cout << ">>>Node2P g: " << node2.Getparent()->Getg() << std::endl;

  
  
  return 0;
}
