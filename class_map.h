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

  // 4=start, 5=target, 6=path
  void SetTypeAt(int x, int y, int t);
  void SetDirAt(int x, int y, int d);

  int GetWidth(){ return width; }
  int GetHeight(){ return height; }
  int GetNnodes(){ return width * height ; }

  std::array<int,2> GetStartLoc() ;
  std::array<int,2> GetTargetLoc() ;

  // function moveCursor from lecture ( needed for ReprintMap() )
  void moveCursor(int deltaX, int deltaY);

  // prints the map to std::cout
  void PrintMap();
  void ReprintMap();

  // returns pointer to the node at the given position
  pfNode* GetNodeAt(int x, int y);
  pfNode* GetNodeAt(std::array<int,2> pos);

  // loads a map from a csv-file. creates new map object and returns pointer to it.
  static pfMap* LoadMap(std::string filename);

  void ResetMap();

};




#endif
