#include <iostream>

#include "class_map.h"
#include "class_node.h"
#include "class_AStar.h"

#include <string>
#include <sstream>
#include <stdio.h>
#include <array>


void plotMap(pfMap Map){

  std::array<std::stringstream, 6> typestream; //Wall, Grass, Forest, visited Grass, visited Forest

  std::array<std::string, 6>  strTypeName  = {"$Wall",
					      "$Grass",
					      "$Forest",
					      "$visitedGrass",
					      "$visitedForest",
					      "$Path"};

  
  std::array<std::string, 6>  strTypeColor  = {"#646464",
					       "#33cc33",
					       "#009933",
					       "#83cc83",
					       "#509983",
					       "yellow"};
 

  double pointsize = 2; 
  
  for(int n=0; n<typestream.size(); n++)
    typestream[n] << strTypeName[n] << "<<" << "EOD\n";
  
  
  
  for(int x=0; x<Map.GetWidth(); x++){
    for(int y=0; y<Map.GetHeight(); y++){

      pfNode *currentNode = Map.GetNodeAt(x,y);
      std::stringstream *currentstream;

      
      if(currentNode->GetIsPath())          // Path
	currentstream = &typestream[5];
      else if(currentNode->GetIsVisited()){

	if(currentNode->GetType() == 2)     // visited Grass
	  currentstream = &typestream[3];   
	else if(currentNode->GetType() == 2)// visited Forest
	  currentstream = &typestream[4];
      }

      else if(currentNode->GetType() == 1)  // Wall
	currentstream = &typestream[0];
      else if(currentNode->GetType() == 2)  // Grass
	currentstream = &typestream[1];
      else if(currentNode->GetType() == 3)  // Forest
	currentstream = &typestream[2];
      
      *currentstream << x << " " << y << "\n";

    }
  }



  

  typestream[0] << "EOD\n" << "plot   $Wall          w p ls 5 ps 2 lc rgb '#646464' \n" ;
  typestream[1] << "EOD\n" << "replot $Grass         w p ls 5 ps 2 lc rgb '#33cc33' \n" ;
  typestream[2] << "EOD\n" << "replot $Forest        w p ls 5 ps 2 lc rgb '#009933'  \n" ;
  typestream[3] << "EOD\n" << "replot $visitedGrass  w p ls 5 ps 2 lt rgb '#83cc83' \n" ;
  typestream[4] << "EOD\n" << "replot $visitedForest w p ls 5 ps 2 lt rgb '#509983  \n" ;
  typestream[5] << "EOD\n" << "replot $Path          w p ls 5 ps 2 lc rgb 'yellow'  \n" ;

 


  FILE *pipeGnu = popen("gnuplot", "w");
  fprintf(pipeGnu, "set term qt persist size 800,800\n");
  fprintf(pipeGnu, "set nokey\n"); 
  fprintf(pipeGnu, "set xlabel \"Width\"\n");
  fprintf(pipeGnu, "set ylabel \"Heigh\"\n");
  fprintf(pipeGnu, "set title \"Map\"\n");
  fprintf(pipeGnu, "set size 1,1\n");

  fprintf(pipeGnu, "set xrange [0:%d]\n", Map.GetWidth()-1);
  fprintf(pipeGnu, "set yrange [0:%d]\n", Map.GetHeight()-1);  


  for(int i=0; i<6; i++){
    fprintf(pipeGnu, "%s\n", typestream[i].str().c_str());
  }
  
  fflush(pipeGnu);
}

int main(){

  pfMap map1(*pfMap::LoadMap("./maps/map1.csv"));

  //pfMap map1(20,30);

 
  pfAStar star1(map1);
  star1.solve("Manhattan", 0, 0, 1);

 
  
  //plotMap(map1);


  return 0;
}
