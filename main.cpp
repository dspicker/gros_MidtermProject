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


pfMap map1(50,20);      // create map on stack
map1.PrintMap();        // print the map to the console
map1.GetNodeAt(3,3)->SetStart() ;   // change something

pfMap* map2 = new pfMap(30,30);   // create another map on the heap
map2->PrintMap();                 // print this one
std::cout << map2->GetNodeAt(4,3)->GetWeight() << std::endl ;  // print weight of a node

pfMap map3(*map2);  // make a copy of map2
map3.PrintMap();    // print the copy

pfMap map4(map1);   // create a copy of map1

delete map2 ;     // delete map from the heap


/*
pfMap* map1 = pfMap::LoadMap("map1.csv") ;
map1->PrintMap();
delete map1 ;
*/


return 0;
}
