#include <vector>
#include <queue>
#include <iostream>

// simple compare function (not lambda function..)
template<typename T>
bool compare(T a,T b){
  return (a>b);
}

// function to print contnent of priority_queue from last to first (?)
template<typename T>
void print(q){
  while(!q.empty()){
    std::cout << q.pop() << " " << std::endl;
    q.pop();  // why do it here again? should the element not be gone alreaydy?
  }
}

// main
int main(){
  std::cout << compare(a,b) << '\n';

}
