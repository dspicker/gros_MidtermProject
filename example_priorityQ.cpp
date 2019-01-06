/*********************************************
 *                                           *
 * How to use std::priority_que - An Example *
 *                                           *
 * Author: Marcel Raabe                      *
 * Date:   06/01/19                          *
 *                                           *
 *********************************************/




#include <iostream>
#include <queue> //for priority_queue
#include <vector>
#include "class_node.cpp"


int main(){

  
  // define compare function (as lambda-function)
  // in this way, prio_que is ordered in the opposite way from smaller to bigger int
  auto compInt = [](int a, int b){return a>b;};

  //initialize prio_queue with compare func, which also has to be in que constructor
  std::priority_queue<int, std::vector<int>, decltype(compInt)> que(compInt);

  // std::priority_queue::push() adds element into the queue and orders it 
  que.push(5);
  que.push(10);
  que.push(2);

  while(!que.empty()){
    std::cout << que.top() << std::endl;
    que.pop();
  }


  std::cout << std::endl <<">>> Now do the same with pfNodes" << std::endl << std::endl;

  
  // define compare function for pfNode
  // pfNodes are ordered by Weight  
  auto compNode = [](pfNode a, pfNode b){return a.GetWeight() < b.GetWeight();};

  std::priority_queue< pfNode, std::vector<pfNode>, decltype(compNode)> que2(compNode);

  que2.push(pfNode(2));
  que2.push(pfNode(3));
  que2.push(pfNode(1));

  while(!que2.empty()){
    // std::priority_queue::top() gives access to top element
    // (!) access is const -> Getter functions has to be const
    std::cout << que2.top().GetWeight() << std::endl;
    que2.pop();
  }
 
  
  return 0;
}
