#pragma once
#include <string>
#include <fstream>

using namespace std;

class Grades{

   string* students;
   double* grades;
   int count = 0;

public:

   Grades(const string& file);

   template<typename function> //template, where type of "function" is an argument , in this case a Letter Lambda function
   void displayGrades(ostream& os, function lambda) const{

      for (int i = 0; i < count; i++){ //For every Student in Grades Object
         auto grade = lambda( grades[i] ); //Run Lambda function passed by and return the string equivalent 
         os << students[i] << " " << grades[i] << " " << grade << endl; //Output Result
      }

   }

   //Prevent copying, moving or assignment of Grades object
   Grades(const Grades& other) = delete;
   Grades& operator=(const Grades& other) = delete;

   //Also Disable move operators
   Grades&& operator=(Grades&& other) = delete;
   Grades(Grades&& other) = delete;

};