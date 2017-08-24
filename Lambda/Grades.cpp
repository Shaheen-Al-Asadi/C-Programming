#pragma once //recall that only header is included, pragma not needed in cpp's?

#include <functional>
#include "Grades.h"
#include <string>
#include <iostream>

Grades::Grades(const string& file){
   
   ifstream is;

   try{

      is.open(file);

      if ( is.fail() ) {
         throw "Error opening file: " + file;
      }

      string buffer;

      //Determine how many records are in a file 
      while ( is.good() ){
         getline(is, buffer, '\n');
         count++; //increment amount of read records
      }

      is.clear(); //clear file stream status [ EOF ] for re-reading
      is.seekg(0, ios::beg); //Return to the begining of file

      students = new string[count]; //Allocate student pointer using count
      grades = new double[count]; //Allocate grade pointer using count
      int i = 0;

      while ( is.good() ){

         //Read S# up until space delimeter
         getline(is, students[i], ' ');

         //Read grade, convert string to INT
         double grade;
         getline(is, buffer, '\n'); //Currently holding a string: 99.9
         grade = stod(buffer); //String TO Double '99.9' is now 99.9
         grades[i] = grade; //Append new grade to array
         i++; //Each i holds same key / value for Student/Grades Arrays
      }

   }//Try

   catch (string& error){
      cout << error << endl;
   }

}