#include <iostream>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"




int main(int argc, char** argv){

  /*
    pfNode n1(1) ;
    pfNode n2(2);
    pfNode n3(3);

    std::cout << n1.GetTypeName() << std::endl ;
    std::cout << n2.GetTypeName() << std::endl ;
    std::cout << n3.GetTypeName() << std::endl ;
  */

  /*
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
  */


  /*
  int n = 50;
  pfMap map1(n,n,0);
  map1.SetTypeAt(2,2,4);
  map1.SetTypeAt(n-3,n-3,5);
  map1.PrintMap();

  auto flow = Breadthfirst(map1);
  bfDrawPath(flow,map1);
  map1.PrintMap();
  */

  pfMap* map1 = pfMap::LoadMap("map2.csv") ;
  //map1->PrintMap();

  pfMap* map5 = new pfMap(*map1) ;
  map5->PrintMap();

  std::cout << "starting breadthfirst" << '\n';
  auto flow2 = Breadthfirst(*map5);
  bfDrawPath(flow2,*map5);
  map5->PrintMap();

  delete map5 ;

  pfMap* map2 = new pfMap(*map1) ;
  // test uniformCost algorithm
  std::cout << "starting uniformCost" << '\n';
  uniformCost(*map2);
  delete map2;

  // delete map(s) created on heap
  delete map1;


  return 0;
}
