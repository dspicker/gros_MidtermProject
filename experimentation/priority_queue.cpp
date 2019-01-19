#include <vector>
#include <queue>
#include <iostream>
#include <array>
#include <map>

//TODO: https://stackoverflow.com/questions/649640/how-to-do-an-efficient-priority-update-in-stl-priority-queue
//      -> just push the updated object and check if poped object is visited
//         and discard if necessary.
//         This could also replace the check if visited before pushing into queue
//         (unnecessary storage)

// function to print content of priority_
template<typename T>
void printQ(T& q){  // can only be used once
  while(!q.empty()){
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << std::endl;
}
// function to fill que
template<typename T>
void fillQ(T &q, int arr[]){
  for(int i=0;i<3;i++){
    q.push(arr[i]);
  }
}

typedef std::array<int,2> locArr;
// function to add two locArrs
locArr addLocArr(locArr &a, locArr &b){
  locArr res;
  for(int i=0; i<2;i++)
    res[i] = a[i] + b[i];
  for(auto e : res)
    std::cout << "addLocArr" << e << '\n';
  return res;
}

// compare functions
bool compare(int a, int b){
  return a>b;
}
bool compare2(int a, int b){
  return a<b;
}
bool compArr(int a[], int b[]){
  return (a[0]+a[1] > b[0] +b[1]);
}

// try at alternavive using library array
bool compArr2(std::array<int,2> a, std::array<int,2> b){
  return (a[0]+a[1] > b[0] +b[1]);
}

// typedef
typedef std::priority_queue<int, std::vector<int>, decltype(&compare)> intPQ;
typedef std::priority_queue< int*, std::vector<int*>,decltype(&compArr) > arrPQ;
typedef std::priority_queue< std::array<int,2>, std::vector<std::array<int,2>>,decltype(&compArr2) > arrPQ2;


// main
int main(){
  int intArr[] = {1,4,2};

/*  prior testing
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

  // using type intPQ

  intPQ q4(&compare);
  fillQ(q4, intArr);
  printQ(q4);

  intPQ q5(&compare2);
  fillQ(q5, intArr);
  printQ(q5);

  // using arrays as entries
  std::cout << std::endl;
  arrPQ aPQ(&compArr);
  int arr1[2] = {1,4};
  int arr2[2] = {2,2};
  aPQ.push(arr1);
  aPQ.push(arr2);
  // print:
  std::cout << aPQ.top()[0] << " " << aPQ.top()[1] << '\n';
  aPQ.pop();
  std::cout << aPQ.top()[0] << " " << aPQ.top()[1] << '\n';
*/

  // using lirbrary arrays
  std::array<int,2> libArr {1,2};
  std::array<int,2> libArr2 {2,2};
  std::array<std::array<int,2>, 2> libArrMatrix {{{1,1}, {3,3}}};  // possible error..

  // using lambda
  auto compArrLambda = [libArr](std::array<int,2> a, std::array<int,2> b){
    std::cout << "libArr of the main scope: " << "libArr = "
              << "[" << libArr[0] << "," << libArr[1] << "]" << '\n';
    return (a[0]+a[1] < b[0] +b[1]);
  };
  typedef std::priority_queue< std::array<int,2>, std::vector<std::array<int,2>>,decltype(compArrLambda) > arrPQL;
  arrPQL PQ(compArrLambda);
  PQ.push(libArr);
  PQ.push(libArr2);
  std::cout << PQ.top()[0] << " " << PQ.top()[1] << '\n';


  // using compArr2
  arrPQ2 libArrPQ(&compArr2);
  libArrPQ.push(libArr);
  std::cout << libArrPQ.top()[0] << " " << libArrPQ.top()[1] << '\n';

  std::array<int,2> test = addLocArr(libArr, libArr2);
  std::cout << test[0] << " " << test[1] << '\n';

  // test behaviour of map::operator[] for nonexistent entry
  std::map<char, int> letter_counts {{'a', 27}, {'b', 3}, {'c', 1}};
  std::cout << letter_counts['a'] << std::endl;
  std::cout << letter_counts['d'] << std::endl;
  std::cout << letter_counts.count('a') << std::endl;
  std::cout << letter_counts.count('d') << std::endl;
  std::cout << letter_counts.count('e') << std::endl;

}
