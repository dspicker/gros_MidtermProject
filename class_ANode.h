#ifndef ANode_h
#define ANode_h

#include "class_node.h"


class ANode : public pfNode{

 private:
  double g; //local value
  double h; //heuristic
  double f; //global value

  ANode *parent; 
  
 public:
  
  // Constructor
  ANode(int i) : pfNode(i){};
  
  ANode()=default;
  
  // Setter:
  void Setg(double _g);
  void Seth(double _h);
  void Setf(double _f);
  void Setparent(ANode *_parent);
  
  // Getter:
  double Getg() const {return g;}
  double Geth() const {return h;}
  double Getf() const {return f;}
  ANode* Getparent() const  {return parent;}

};



#endif
