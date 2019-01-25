#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

int main(){

  std::fstream inFile("dataPerformance.gnu");

  std::string line;
  std::stringstream  sstream ;


  FILE *pipeGnu = popen("gnuplot", "w");

  while (std::getline(inFile, line))
    {

      sstream << line << "\n";
    }

  line = sstream.str();

  fprintf(pipeGnu, line.c_str());

  fflush(pipeGnu);

  std::cin >> line;

}
