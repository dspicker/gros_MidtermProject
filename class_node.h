#ifndef pfNode_h
#define pfNode_h

#include <string>


class pfNode {
protected:
  // type of node. 1 wall, 2 grass, 3 forest, 4 start-node, 5 target-node, 6 path
  int type ;
  // weight depends on the type. grass 1, forest 5, wall -1, rest 1
  int weight;

  bool isPath = false;
  bool isVisited = false;

  double f=-1;
  int direction = 0;  // 1 right, 2 up, 3 left, 4 down .

public:
  // Constructor:
  // Should be used for initializing pfNode
  pfNode(int t);

  //can be used, for createing *pfNode
  pfNode()=default;

  // Getter:
  // Should be const, expecially for using a std::priority_queue
  int GetType() const { return type; }
  int GetWeight() const { return weight; }
  std::string GetTypeName() const; // returns "Wall", "Grass", etc..


  // Setter:
  // set the node as a start or end point of the path.
  void SetStart();
  void SetTarget();
  void SetPath();
  void SetIsPath();  // ToDo: mit SetPath vereinheitlichen
  void SetIsVisited();
  void ResetIsPath(); // TODO: nach vereinheitlichung obselet.
  void ResetIsVisited();
  void Setf(double _f);

  void setDirection(int dir);

  // prints the node to std::cout with an rgb colored whitespace
  void Print();

// additional types to visualize visited/checked nodes (Felix) :
  void setType(int type);
  void getType(int type);
// end of additions (Felix)


};



#endif
