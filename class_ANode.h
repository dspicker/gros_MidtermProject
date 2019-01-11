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
  bool Viseted=false;

  std::vector<ANode*> Neighbours;

  const std::array<int,2> Position;
  
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
  void Setf(double _f);
  void SetParent(ANode *_parent);
  
  // Getter:
  double Getg() const {return g;}
  double Geth() const {return h;}
  double Getf() const {return f;}
  ANode* GetParent() const  {return Parent;}
  bool isVisited() const {return Viseted;}
  std::vector<ANode*> GetNeighbours() const {return Neighbours;}
  
};
#endif
