#include <iostream>

#include "class_node.h"
#include "class_map.h"

int main(int argc, char** argv){

  /*
    pfNode n1(1) ;
    pfNode n2(2);
    pfNode n3(3);

    std::cout << n1.GetTypeName() << std::endl ;
    std::cout << n2.GetTypeName() << std::endl ;
    std::cout << n3.GetTypeName() << std::endl ;
  */
  pfMap map1(50,50);

  map1.PrintMap();

  //std::cout <<  << std::endl ;

  map1.GetNodeAt(49,49)->SetTarget() ;
  map1.GetNodeAt(1,1)->SetTarget() ;
 
  map1.PrintMap();

  return 0;
}
