#ifndef pfMap_h
#define pfMap_h

#include "class_node.h"
#include <vector>

class pfMap {
private:
  int width;   // number of nodes in horizontal direction
  int height;  // number of nodes in vertical direction

  std::vector<pfNode> nodes;

public:
  // constructor to initialise the map with random nodes
  pfMap(int w, int h);

  void SetWidth(int w) ;
  void SetHeight(int h) ;


  int GetWidth(){ return width; }
  int GetHeigth(){ return height; }
  int GetNnodes(){ return width * height ; }



};




#endif
