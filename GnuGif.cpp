#include <iostream>

#include "class_map.h"
#include "class_node.h"
#include "class_AStar.h"

#include <string>
#include <sstream>
#include <stdio.h>
#include <array>

#include <unistd.h>


void GnuGif(pfMap Map){

  static bool firsttime = true; 


  
  std::array<std::stringstream, 8> typestream; //Wall, Grass, Forest, visited Grass, visited Forest, Start, Finish

  
  std::array<std::string, 8>  strTypeName  = {"$Wall",
					      "$Grass",
					      "$Forest",
					      "$visitedGrass",
					      "$visitedForest",
					      "$Path",
					      "$Start",
					      "$Finish"};
  
  // Starting Streams
  for(int n=0; n<typestream.size(); n++)
    typestream[n] << strTypeName[n] << "<<" << "EOD\n";
  
  
  // Fill Map Nodes into Streams
  for(int x=0; x<Map.GetWidth(); x++){
    for(int y=0; y<Map.GetHeight(); y++){

      pfNode *currentNode = Map.GetNodeAt(x,y);
      std::stringstream *currentstream;

      if(currentNode->GetType() == 4)      // Start
	currentstream = &typestream[6];
      else if(currentNode->GetType() == 5) // Finish
	currentstream = &typestream[7];
            
      else if(currentNode->GetIsPath())     // Path
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

  
  static FILE *pipeGnu = popen("gnuplot", "w");

  if (firsttime){

    // Set Up Gnuplot
    fprintf(pipeGnu, "reset\n");            
    fprintf(pipeGnu, "set term gif animate {delay 1} size 800,800\n");
    fprintf(pipeGnu, "set output \"animate.gif\"\n");

    //fprintf(pipeGnu, "set term w size 800,800\n");
    fprintf(pipeGnu, "set nokey\n"); 
    fprintf(pipeGnu, "set xlabel \"Width\"\n");
    fprintf(pipeGnu, "set ylabel \"Heigh\"\n");
    fprintf(pipeGnu, "set title \"Map\"\n");
    fprintf(pipeGnu, "set size 1,1\n");

    fprintf(pipeGnu, "set xrange [0:%d]\n", Map.GetWidth()-1);
    fprintf(pipeGnu, "set yrange [0:%d]\n", Map.GetHeight()-1);  
  
    // Define Plots
    typestream[0] << "EOD\n" << "plot   $Wall          w p ls 5 ps 2.5 lc rgb '#646464' \n" ;
    typestream[1] << "EOD\n" << "replot $Grass         w p ls 5 ps 2.5 lc rgb '#33cc33' \n" ;
    typestream[2] << "EOD\n" << "replot $Forest        w p ls 5 ps 2.5 lc rgb '#009933'  \n" ;
    typestream[3] << "EOD\n" << "replot $visitedGrass  w p ls 5 ps 2.5 lt rgb '#83cc83' \n" ;
    typestream[4] << "EOD\n" << "replot $visitedForest w p ls 5 ps 2.5 lt rgb '#509983  \n" ;
    typestream[5] << "EOD\n" << "replot $Path          w p ls 5 ps 2.5 lc rgb 'yellow'  \n" ;
    typestream[6] << "EOD\n" << "replot $Start         w p ls 5 ps 2.5 lc rgb 'red'  \n" ;
    typestream[7] << "EOD\n" << "replot $Finish        w p ls 5 ps 2.5 lc rgb 'blue'  \n" ;

    
  }
  else{
    // Just Replot here
    for(int i=0; i<8; i++)
      typestream[i] << "EOD\n" << "replot\n";
  }
 

  // Send Streams to Gnuplot
  for(int i=0; i<8; i++){
    fprintf(pipeGnu, "%s\n", typestream[i].str().c_str());
  }
  
  fflush(pipeGnu);
  
  firsttime = false;
}



/*



  
  std::array<std::string, 6>  strTypeColor  = {"#646464",
  "#33cc33",
  "#009933",
  "#83cc83",
  "#509983",
  "yellow"};
 

  double pointsize = 2; 
*/
