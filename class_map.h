#ifndef pfMap_h
#define pfMap_h

#include <vector>

class pfMap {
private:
  const int width;   // number of nodes in horizontal direction
  const int height;  // number of nodes in vertical direction

  std::vector<pfNode> nodes;

public:
  // default constructor
  pfMap();
  // constructor to initialise the map with random nodes
  pfMap(int w, int h): width(w), height(h) ;

  void SetWidth(int w) ;
  void SetHeight(int h) ;


  int GetWidth(){ return width; }
  int GetHeigth(){ return height; }
  int GetNnodes(){ return width * height ; }



};




#endif
