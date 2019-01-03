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
pfMap map1(50,20);

pfMap* map2 = new pfMap(30,30);

map1.PrintMap();

//std::cout <<  << std::endl ;

map1.GetNodeAt(3,3)->SetStart() ;
map1.GetNodeAt(3,3)->GetWeight() ;

map1.PrintMap();

map2->PrintMap();
map2->GetNodeAt(4,3)->GetWeight() ;

delete map2 ;


return 0;
}
