#ifndef asNode_h
#define asNode_h

#include "class_node.h"
#include <vector>
#include <array>

class asNode : public pfNode{

 private:
  double g; //local value
  double h; //heuristic
  double f; //global value

  asNode *Parent=NULL; 
  bool Visited=false;

  std::vector<asNode*> Neighbors;

  std::array<int,2> Position;
  
  //-------------------------------------------------------------------------------------------------
 public:
  
  // Constructor
  //asNode(std::array<int,2> _position, int i) : pfNode(i),  Position(_position) {};
 asNode(std::array<int,2> _position, pfNode *_node) : pfNode(_node->GetType() ), Position(_position) {};

  // asNode(int i) : pfNode(i) {};
  // asNode(pfNode &_node) : pfNode(_node.GetType()) {};
  asNode()=default;
  
  // Setter:
  void Setg(double _g);
  void Seth(double _h);
  void Setf();
  void SetParent(asNode &_parent);
  void SetNeighbor(asNode &_neighbor);
  void SetVisited();
    
  // Getter:
  double* Getg() {return &g;}
  double* Geth() {return &h;}
  double* Getf() {return &f;}
  
  asNode* GetParent() const  {return Parent;}
  bool* isVisited() {return &Visited;}
  std::vector<asNode*>* GetNeighbors() {return &(Neighbors);}
  std::array<int,2> GetPosition() {return Position;}
  std::array<int,2>* GetPositionRef() {return &Position;}

 
};
#endif
