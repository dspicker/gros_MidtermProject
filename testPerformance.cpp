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

/* TODO:
    - delete old code or keep option for both time and iterations?
    - use pointer to int instead
    -

*/



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

  bool useTime=false; // keep option to compare time?

  typedef std::array<int,2> locArr; // can be deleted?
/*  old using time
    std::chrono::high_resolution_clock::time_point t1_breadth, t2_breadth,
                                                   t1_uniform, t2_uniform,
                                                   t1_star, t2_star,
                                                   t1_greedy, t2_greedy;

    std::chrono::duration<double> duration_breadth;
    std::chrono::duration<double> duration_uniform;
    std::chrono::duration<double> duration_greedy;
    std::chrono::duration<double> duration_star;
*/
  int itCount_breadth, itCount_uniform, itCount_greedy, itCount_star;

  std::vector<double> vBreadth, vUniform, vStar, vGreedy;
  std::vector<int> vNodes;

/*  old using time
  size_t int_duration_breadth, int_duration_uniform,
         int_duration_star, int_duration_greedy;
*/

  int width  = 10;
  int height = 10;

  int sampleSize = 10; // use to calculate average itCount in the end?
  int maxMapSize = 80;

  for(int m=10; m<=maxMapSize; m+=10){  // iteration over map size

    width = m;
    height = m;
    // reset totInt counters:
    int totIt_breadth = 0;
    int totIt_uniform = 0;
    int totIt_greedy = 0;
    int totIt_star = 0;


/*  old using time
    duration_breadth.zero();
    duration_uniform.zero();
    duration_star.zero();
    duration_greedy.zero();
*/

    for(int n=0; n<sampleSize; n++){  // iteration over sample size

      // create map and set start- and targetlocation
      pfMap map(width, height);
      map.SetTypeAt(1,1,4);   // set start location
      map.SetTypeAt(width-2,height-2,5);  // set target location

      // create copies of map (is this even needed here?)
      pfMap map_breadth(map);
      pfMap map_uniform(map);
      pfMap map_AStar(map);
      pfMap map_greedy(map);
      // create AStar object
      pfAStar star(map);

      // (re)set iteration counters:
      itCount_breadth = 0;
      itCount_uniform = 0;
      itCount_star = 0;
      itCount_greedy = 0;

      // run algorithms on maps
      Breadthfirst(map_breadth,0,0,&itCount_breadth);
      totIt_breadth += itCount_breadth;

      uniformCost(map_uniform,0,0,&itCount_uniform);
      totIt_uniform += itCount_uniform;

      GreedyBestFirst(map_greedy,0,0,&itCount_greedy);
      totIt_greedy += itCount_greedy;

      star.solve("Manhattan",0,0,&itCount_star);
      totIt_star += itCount_star;

/*    old using time
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
*/
    }
/*  old using time
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
*/

    // calculate average
    totIt_breadth = totIt_breadth/sampleSize;
    totIt_uniform = totIt_uniform/sampleSize;
    totIt_greedy = totIt_greedy/sampleSize;
    totIt_star = totIt_star/sampleSize;



    vBreadth.push_back(totIt_breadth);
    vUniform.push_back(totIt_uniform);
    vGreedy.push_back(totIt_greedy);
    vStar.push_back(totIt_star);
    vNodes.push_back(width*height);

    std::cout << "\n>>>" << m << "x" << m << " nodes:"
        << "\nBreadth: " << totIt_breadth
        << "\nUniform: " << totIt_uniform
        << "\nGreedy : "   << totIt_greedy
        << "\nStar   : " << totIt_star
        << std::endl;


/*  old using time
    std::cout << "\n>>>" << m << "x" << m << " nodes:"
	      << "\nBreadth: " << int_duration_breadth
	      << "\nUniform: " << int_duration_uniform
        << "\nGreedy : "   << int_duration_greedy
	      << "\nStar   : " << int_duration_star
	      << std::endl;
*/
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
