#ifndef pfMap_h
#define pfMap_h

#include "class_node.h"
#include <map>
#include <array>


class pfMap {
private:
  int width;   // number of nodes in horizontal direction
  int height;  // number of nodes in vertical direction


  std::map< std::array<int,2>, pfNode > nodes ;
  // eventuell doch vector?

  std::array<int,2> start_loc;
  std::array<int,2> target_loc;
public:
  // default constructor
  pfMap();

  // constructor to initialise the map with random weighted nodes
  pfMap(int w, int h);

  // constructor to initialise the map with random nodes
  pfMap(int w, int h, bool weighted);

  // copy constructor
  pfMap(pfMap &old);

  void SetWidth(int w){ width=w; }
  void SetHeight(int h){ height=h; }

  void SetStartAt(int x, int y);
  void SetTargetAt(int x, int y);

  int GetWidth(){ return width; }
  int GetHeigth(){ return height; }
  int GetNnodes(){ return width * height ; }

  std::array<int,2> GetStartLoc() ;
  std::array<int,2> GetTargetLoc() ;

  // prints the map to std::cout
  int PrintMap();

  // returns pointer to the node at the given position
  pfNode* GetNodeAt(int x, int y);

  // loads a map from a csv-file. creates new map object and returns pointer to it.
  static pfMap* LoadMap(std::string filename);


};




#endif
