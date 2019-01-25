#include <iostream>

#include "class_node.h"
#include "class_map.h"
#include "uniformCost.cpp"
#include "breadthfirst.cpp"
#include "class_AStar.h"
#include "greedyBestFirst.cpp"

#include <chrono>
#include <string>
#include <sstream>
#include <stdio.h>



std::string toGnuplot(std::vector<int> &x, std::vector<double> &y, std::string dataName){

  std::stringstream ss;
  ss << dataName << " << " << "EOD\n";

  for(size_t i=0; i<x.size(); i++){
    ss << x[i] << " " << y[i] << std::endl;
  }
  ss << "EOD\n";

  return ss.str();
}




int main(){

  typedef std::array<int,2> locArr; // can be deleted?

  std::chrono::high_resolution_clock::time_point t1_breadth, t2_breadth,
                                                 t1_uniform, t2_uniform,
                                                 t1_star, t2_star,
                                                 t1_greedy, t2_greedy;
  std::chrono::duration<double> duration_breadth;
  std::chrono::duration<double> duration_uniform;
  std::chrono::duration<double> duration_greedy;
  std::chrono::duration<double> duration_star;

  std::vector<double> vBreadth, vUniform, vStar, vGreedy;
  std::vector<int> vNodes;


  size_t int_duration_breadth, int_duration_uniform,
         int_duration_star, int_duration_greedy;

  int width  = 10;
  int height = 10;

  int sampleSize = 10; // use to calculate average time in the end?
  int maxMapSize = 50;

  for(int m=10; m<=maxMapSize; m+=10){

    width = m;
    height = m;

    duration_breadth.zero();
    duration_uniform.zero();
    duration_star.zero();
    duration_greedy.zero();

    for(int n=0; n<sampleSize; n++){

      pfMap map(width, height);
      map.SetTypeAt(1,1,4);   // set start location
      map.SetTypeAt(width-2,height-2,5);  // set target location

      // copy maps (is this even needed here?)
      pfMap map_breadth(map);
      pfMap map_uniform(map);
      pfMap map_AStar(map);
      pfMap map_greedy(map);
      // create AStar object
      pfAStar star(map);

      t1_breadth = std::chrono::high_resolution_clock::now();
      Breadthfirst(map_breadth);
      t2_breadth = std::chrono::high_resolution_clock::now();
      duration_breadth += (t2_breadth - t1_breadth);

      t1_uniform = std::chrono::high_resolution_clock::now();
      uniformCost(map_uniform);
      t2_uniform = std::chrono::high_resolution_clock::now();
      duration_uniform += (t2_uniform-t1_uniform);

      t1_greedy = std::chrono::high_resolution_clock::now();
      GreedyBestFirst(map_greedy);
      t2_greedy = std::chrono::high_resolution_clock::now();
      duration_greedy += (t2_greedy-t1_greedy);

      t1_star = std::chrono::high_resolution_clock::now();
      star.solve("Manhattan");
      t2_star = std::chrono::high_resolution_clock::now();
      duration_star += (t2_star-t1_star);
    }

    int_duration_breadth = std::chrono::duration_cast<std::chrono::microseconds>
                           (duration_breadth).count()/sampleSize;
    int_duration_uniform = std::chrono::duration_cast<std::chrono::microseconds>
                           (duration_uniform).count()/sampleSize;
    int_duration_greedy  = std::chrono::duration_cast<std::chrono::microseconds>
                           (duration_greedy).count()/sampleSize;
    int_duration_star    = std::chrono::duration_cast<std::chrono::microseconds>
                           (duration_star).count()/sampleSize;

    vBreadth.push_back(int_duration_breadth);
    vUniform.push_back(int_duration_uniform);
    vGreedy.push_back(int_duration_greedy);
    vStar.push_back(int_duration_star);
    vNodes.push_back(width*height);

    std::cout << "\n>>>" << m << "x" << m << " nodes:"
	      << "\nBreadth: " << int_duration_breadth
	      << "\nUniform: " << int_duration_uniform
        << "\nGreedy:"   << int_duration_greedy
	      << "\nStar   : " << int_duration_star
	      << std::endl;

  }



  //FILE *pipeGnu = popen("gnuplot", "w");  // to plot directly ???

  FILE *pipeGnu = fopen("./dataPerformance/dataPerformance.gnu","w"); // create plot file

  fprintf(pipeGnu, "set xrange [0:10000]\n");
  //fprintf(pipeGnu, "set yrange [1:500000]\n");
  fprintf(pipeGnu, "set logscale y\n");
  fprintf(pipeGnu, "set xlabel \"Number of Nodes\"\n");
  fprintf(pipeGnu, "set ylabel \"t [ms]\"\n");
  fprintf(pipeGnu, "set title \"Performance comparison\"\n");

  std::string dataToPlot;
  std::string Name;

  Name = "$Breadthfirst";
  dataToPlot = toGnuplot(vNodes, vBreadth, Name);

  fprintf(pipeGnu, "%s\n",dataToPlot.c_str());
  fprintf(pipeGnu, "plot \"%s\" w lines lw 3\n", Name.c_str() );


  Name = "$UniformCost";
  dataToPlot = toGnuplot(vNodes, vUniform, Name);

  fprintf(pipeGnu, "%s\n",dataToPlot.c_str());
  fprintf(pipeGnu, "replot \"%s\" w lines lw 3\n", Name.c_str() );

  Name = "$GreedyBestFirst";
  dataToPlot = toGnuplot(vNodes, vGreedy, Name);

  fprintf(pipeGnu, "%s\n",dataToPlot.c_str());
  fprintf(pipeGnu, "replot \"%s\" w lines lw 3\n", Name.c_str() );

  Name = "$AStar";
  dataToPlot = toGnuplot(vNodes, vStar, Name);

  fprintf(pipeGnu, "%s\n",dataToPlot.c_str());
  fprintf(pipeGnu, "replot \"%s\" w lines lw 3\n", Name.c_str() );


  fflush(pipeGnu);

  return 0;
}
