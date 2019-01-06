#ifndef ANode_h
#define ANode_h

#include "class_node.h"


class ANode : public pfNode{

 private:
  double g;
  double h;
  double f;


 public:
  
  // Constructor
  ANode(int i) : pfNode(i){};
  
  //ANode()=default;
  
  // Setter:
  void Setg(double _g);
  void Seth(double _h);
  void Setf(double _f);
  
  // Getter:
  double Getg() const {return g;}
  double Geth() const {return h;}
  double Getf() const {return f;}
  

};



#endif
