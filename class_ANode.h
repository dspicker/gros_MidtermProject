#ifndef ANode_h
#define ANode_h

#include "class_node.h"
#include <vector>
#include <array>

class ANode : public pfNode{

 private:
  double g; //local value
  double h; //heuristic
  double f; //global value

  ANode *Parent=NULL; 
  bool Visited=false;

  std::vector<ANode*> Neighbours;

  std::array<int,2> Position;
  
  //-------------------------------------------------------------------------------------------------
 public:
  
  // Constructor
  //ANode(std::array<int,2> _position, int i) : pfNode(i),  Position(_position) {};
 ANode(std::array<int,2> _position, pfNode *_node) : pfNode(_node->GetType() ), Position(_position) {};

  // ANode(int i) : pfNode(i) {};
  // ANode(pfNode &_node) : pfNode(_node.GetType()) {};
  ANode()=default;
  
  // Setter:
  void Setg(double _g);
  void Seth(double _h);
  void Setf();
  void SetParent(ANode &_parent);
  void SetNeighbour(ANode &_neighbour);
  void SetVisited();
    
  // Getter:
  double* Getg() {return &g;}
  double* Geth() {return &h;}
  double* Getf() {return &f;}
  
  ANode* GetParent() const  {return Parent;}
  bool* isVisited() {return &Visited;}
  std::vector<ANode*>* GetNeighbours() {return &(Neighbours);}
  std::array<int,2> GetPosition() {return Position;}
  std::array<int,2>* GetPositionRef() {return &Position;}

 
};
#endif
