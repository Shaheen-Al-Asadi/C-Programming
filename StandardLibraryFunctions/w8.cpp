// Workshop 8 - STL Algorithms
// w8.cpp
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "DataTable.h"

//The first command - line argument is the name of the file to analyze.
//The second argument, if present, requests a listing of all data values retrieved by the object.

const int FW = 7;
const int ND = 2;

int main(int argc, char** argv) {

   std::cout << "\nCommand Line : ";
   for (int i = 0; i < argc; i++) {
      std::cout << argv[i] << ' ';
   }
   std::cout << std::endl;

   if (argc != 2 && argc != 3) {
      std::cerr << argv[0] << ": incorrect number of arguments\n";
      std::cerr << "Usage: " << argv[0] << " file_name [p]\n";
      return 1; //incorrect usage? return 1
   }

   std::ifstream dataFile(argv[1]); //initialized dataFile here using supplied file.dat
   if (!dataFile) {
      std::cerr << "\n***Failed to open file " << argv[1] << "***\n";
      return 2; //file not good?return 2 
   }

   try {
      w8::DataTable<float> data(dataFile, FW, ND); //DataTable taking in floats as template type, and creating data using file, field width and decimals to display [constants]
      if (argc == 3) { //if 3 arguments supplied, .exe , file and a third - print out data that was initialized in dataTable
         std::cout << "\nData Values\n===========\n";
         std::cout << data << std::endl;
      }
      float m, c;
      data.regression(m, c); //dataTable function

      std::cout << "\nStatistics\n==========\n";
      std::cout << std::fixed << std::setprecision(ND); //Report format logic using decimals and fields for beautiful output
      std::cout << "y mean    = " << std::setw(FW) << data.mean() << //mean
         "\ny sigma   = " << std::setw(FW) << data.sigma() << //sigma
         "\ny median  = " << std::setw(FW) << data.median() << std::endl; //median
      std::cout << "slope     = " << std::setw(FW) << m << //m result from regression
         "\nintercept = " << std::setw(FW) << c << std::endl; //c from regression
   }
   catch (std::string& msg) {
      std::cout << msg << std::endl; //problem? catch return 3
      return 3;
   }

   std::cout << "\nPress any key to continue ... ";
   std::cin.get();
}
