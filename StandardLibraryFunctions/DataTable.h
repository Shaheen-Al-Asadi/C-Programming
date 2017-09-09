#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <numeric> //accumulate 
#include <algorithm>  //sort
//#include <utility> //move

using namespace std;

namespace w8{

   template<class T>
   class DataTable{

      int width;
      int decimals;
      vector <T> x;
      vector <T> y;

   public:

      DataTable(ifstream& is, int w, int d) : width(w), decimals(d){

         while (is.good()){ //Loop through file

            string line;
            getline(is, line);
            stringstream ss; //will deconstruct the line to push back proper coordinates

            if (!line.empty()){

               ss.str(line);//fill in ss

               T xBuffer, yBuffer; //initialize 2 variables of type t

               ss >> xBuffer >> yBuffer; //extract until space until buffer1 , buffer 2 
               //could skip this step and getline until ' ' from line[29] twice into seperate buffers but then have discern into type T somehow

               //push back into respective vector
               x.push_back(xBuffer);
               y.push_back(yBuffer);

            }//if line not empty

         }// until eof

      } //ctor

      //Recall that you are still within class definition for this template instance

      //T mean() const - returns the mean value of the dependent coordinate
      T mean() const{ //adds up total from specified range, provided intial value 0.0 for total
         T Total = accumulate(y.begin(), y.end(), 0.0);
         return Total / y.size(); //No need to cast into double, it will be of T type 
      }

      //T sigma() const - returns the standard deviation of the dependent coordinates
      // unicode error pasting the forumla: sample standard deviation online
      T sigma() const{
         T Mean = mean();
         T DeviationT = 0.0;
         for (int i = 0; i < y.size(); ++i) {
            DeviationT += (y[i] - Mean) * (y[i] - Mean);
            // What a pain, stack over flow explained
            //Step by step mathematical instructions
         }
         return sqrt(DeviationT / y.size());
      }
    //template <class InputIterator, class Function>
    //Function for_each (InputIterator first, InputIterator last, Function fn);

      //T median() const - returns the median value of the dependent coordinate
      T median() const{      
         vector<T> Temp = y; //copy over y vector on a temp vector
         sort( Temp.begin(), Temp.end() ); //Sorts the elements in the range [first,last) into ascending order.
         T median = Temp[Temp.size() / 2]; //Temp being manipulated [ to find middle index ] of temp 
         return median;
      }

      //void regression(T& slope, T& y_intercept) const - returns the slope and intercept for the data set
      //SLOPE and Y intercept containers are both provided as floasts from main
      //help provided from forum and ecil
      void regression(T& slope, T& y_intercept) const{

         // average of values
         T Xavg = accumulate(x.begin(), x.end(), 0.0) / x.size(); //added up values and divive for avg
         T Yavg = accumulate(y.begin(), y.end(), 0.0) / y.size();

         T n = 0.0;//numerator
         T d = 0.0;//denominator

         for (int i = 0; i < x.size(); ++i){
            n += (x[i] - Xavg) * (y[i] - Yavg);
            d += (x[i] - Xavg) * (x[i] - Xavg);
         }

         slope = n/d;
         y_intercept = Yavg - (slope * Xavg);

      }

      //void display(std::ostream&) const - displays the data pairs as shown below
      void display(ostream& os) const{
         //cout << "Data Values" done by main already
         os << setw(width) << "x"
            << setw(width) << "y" << "\n"; //first row as headers

         for (int i = 0; i < x.size(); i++){ 
            os << setw(width) << fixed << setprecision(decimals) << x[i]
               << setw(width) << fixed << setprecision(decimals) << y[i] << "\n";
         }
      }

   }; //End of DataTable Template

   //std::ostream& operator<<(std::ostream&, const DataTable&) --hinting helper func
   //inserts the data generated by display() into the output stream
   template<class T>
   ostream& operator<<(ostream& os, const DataTable<T>& dt){
      dt.display(os);
      return os;
   }
}
