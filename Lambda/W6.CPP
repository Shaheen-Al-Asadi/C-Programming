// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include <functional> //For function objects used in previous version
#include <string>
#include "Grades.h"

int main(int argc, char* argv[]) {
  
   /*
   if (argc != 2) {
      std::cerr << argv[0] <<
         ": incorrect number of arguments\n";
      std::cerr << "Usage: " << argv[0] << " file_name\n";
      return 1;
   }
   */

   //Grades grades(argv[1]);
   std::string filename = "Grades.dat"; //For easy no CLI testing
   Grades grades(filename);

   // define the lambda expression for letter
   auto letter = [](double grade){ //Nothing in capture list, takes in a double of grade
                                   //returns an auto type "string" based on what the grade value is
      if (grade < 50) { 
         return "F";
      }
      else if (grade < 55) {
         return "D";
      }
      else if (grade < 60) {
         return "D+";
      }
      else if (grade < 65) {
         return "C";
      }
      else if (grade < 70) {
         return "C+";
      }
      else if (grade < 75) {
         return "B";
      }
      else if (grade < 80) {
         return "B+";
      }
      else if (grade < 90) {
         return "A";
      }
      else if (grade >= 90) {
         return "A+";
      }
      
   }; //End of Lambda , TO DO: Return an error else if? 

   grades.displayGrades(std::cout, letter);//Call displayGrades method, take in OS reference and Lambda Function

   std::cout << "Press any key to continue ... ";
   std::cin.get();
}