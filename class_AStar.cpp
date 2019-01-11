#include "class_AStar.h"

#include "class_node.h"
#include "class_map.h"


#include <map>
#include <array>



void pfAStar::SetNodes(){


  for(int x=0; x<map.GetWidth(); x++){
    for(int y=0; y<map.GetHeigth(); y++){

      std::array<int,2> koord = {x,y};
      ANode a(koord, map.GetNodeAt(x,y));
    allNodes.push_back(a);
      
    }
  }
}
