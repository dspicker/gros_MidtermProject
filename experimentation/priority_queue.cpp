#include <vector>
#include <queue>
#include <iostream>
#include <array>

//TODO: https://stackoverflow.com/questions/649640/how-to-do-an-efficient-priority-update-in-stl-priority-queue

// function to print contnent of priority_queue from last to first (?)
template<typename T>
void printQ(T& q){  // can only be used once
  while(!q.empty()){
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << std::endl;
}
// compare function (only integer)
bool compare(int a, int b){
  return a>b;
}
// function to fill que
template<typename T>
void fillQ(T &q, int arr[]){
  for(int i=0;i<3;i++){
    q.push(arr[i]);
  }
}


// main
int main(){
  int a = 1;
  int b = 4;
  int c = 2;
  int intArr[] = {a,b,c};

  // default
  std::priority_queue<int> q;
//  for(int i : intArr)
//    q.push(i);
  fillQ(q, intArr);
  printQ(q);

  // with custom compare function using lambda:
  auto comp = [](int a, int b){return a>b;};
  std::priority_queue<int,std::vector<int>, decltype(comp)> q2(comp);
  fillQ(q2, intArr);
  printQ(q2);

  // using normal function compare
  std::priority_queue<int, std::vector<int>, decltype(&compare)> q3(&compare);
  fillQ(q3, intArr);
  printQ(q3);
}
