#include <vector>
#include <queue>
#include <iostream>

// simple compare function (not lambda function..)
template<typename T>
bool compare(T a,T b){
  return (a>b);
}

int main(){
  double a = 3;
  double b = 2.0;
  std::cout << compare(a,b) << '\n';
}
