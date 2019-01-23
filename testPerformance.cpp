#include <iostream>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"
#include "class_AStar.h"

#include <chrono> 


int main(int argc, char** argv){

  typedef std::array<int,2> Location ;
  typedef std::array<int,2> locArr;



  //  std::chrono::high_resolution_clock

  std::chrono::high_resolution_clock::time_point t1_breadth, t2_breadth, t1_uniform, t2_uniform, t1_star, t2_star;
  std::chrono::duration<double> duration_breadth;
  std::chrono::duration<double> duration_uniform;
  std::chrono::duration<double> duration_star;

  int width  = 10;
  int height = 10;
  
  for(int m=10; m<=100; m=m+10){

    width = m;
    height = m;

    duration_breadth.zero();
    duration_uniform.zero();
    duration_star.zero();
    
    for(int n=0; n<1000; n++){
    
      pfMap map(width, height);
      map.GetNodeAt(1,1)->SetStart();
      map.GetNodeAt(width-2,height-2)->SetTarget();

      pfMap map_breadth(map);
      pfMap map_uniform(map);
      pfMap map_AStar(map);
      pfAStar star(map);
  
      //map.PrintMap();
    
      t1_breadth = std::chrono::high_resolution_clock::now();
      std::map< Location, Location > Breadth = Breadthfirst(map_breadth);
      t2_breadth = std::chrono::high_resolution_clock::now();
      duration_breadth += t2_breadth - t1_breadth;

      t1_uniform = std::chrono::high_resolution_clock::now();
      std::map<locArr, locArr> Uniform = uniformCost(map_uniform);
      t2_uniform = std::chrono::high_resolution_clock::now();
      duration_uniform += t2_uniform-t1_uniform;
    
      t1_star = std::chrono::high_resolution_clock::now();
      star.solve("Manhattan");
      t2_star = std::chrono::high_resolution_clock::now();
      duration_star += t2_star-t1_star;
    }

    std::cout << "\n>>>" << m << "x" << m << " nodes:" 
	      << "\nBreadth: " << duration_breadth.count()
	      << "\nUniform: " << duration_uniform.count()
	      << "\nStar   : " << duration_star.count()
	      << std::endl;
		   
  }



  return 0;
}
