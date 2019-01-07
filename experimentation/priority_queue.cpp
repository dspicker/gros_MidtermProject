#include <vector>
#include <queue>
#include <iostream>

// function to print contnent of priority_queue from last to first (?)
template<typename T>
void printQ(T& q){  // can only be used once
  while(!q.empty()){
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << std::endl;
}

// main
int main(){
  int intArr[] = {1,5,9,10,30,3,3,4,1};

  // default
  std::priority_queue<int> q;
  for(int i : intArr)
    q.push(i);
  printQ(q);

  // with custom compare function using lambda:
  // (alternative would be structure with comparison function..?)
  auto comp = [](int a, int b){return a>b;};
  std::priority_queue<int,std::vector<int>, decltype(comp)> q2(comp);
}
