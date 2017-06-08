#pragma once
#include "util.h" //connect the header within cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility> //move
#include <algorithm>//for delSpaces function
#include <sstream> 

using namespace std;

/*BUG LIST
CSV Row cannot end with a delimeter 
Field is not toLower() , "MEMORY" will not match with "Memory" during integrity tests
If an Item is ordered twice in one Order, integrity check will report it as not found??
*/


/*
SPEC:
Pick up the filename and separator character from the command line.
Read the file, line, by line.
Splitting each line in a vector of string fields.Trim leading and trailing spaces ' ' from each field. - Need to Trim Incoming Fields before placing in vector
Store the vector of string fields into a vector of lines.
This forms a 2 - dimensional vector - vector - string table : vector< vector< string > > csvData;
Print the csvData out three ways using indices, iterators, and range - based for loops.

*/

string delSpaces(string &str) {  
   //While string not empty, if there is a space in front index, erase, if space in last index, erase
   //while (!str.empty() && isspace(*str.begin())){ str.erase(str.begin()); }
   //while (!str.empty() && isspace(*str.rbegin())){ str.erase(str.length() - 1); }

   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
   return str;
}

//Takes in a CSV vector and prints contents 3 different ways
void csvPrint(std::vector < vector<string> >& data) {

   //Test printing the data three ways

   cout << "\nMethod 1 - range - based for loop:\n";

   for (auto line : data) {
      for (auto field : line) {
         cout << field << " ";
      }
      cout << "\n";
   }

   cout << "\nMethod 2 - conventional for loop:\n";

   for (int line = 0; line < data.size(); line++) {
      for (int field = 0; field < data[line].size(); field++) {
         cout << data[line][field] << " ";
      }
      cout << "\n";
   }

   cout << "\nMethod 3 - iterator for loop:\n";

   for (auto line = data.begin(); line < data.end(); line++) {

      for (auto field = line->begin(); field < line->end(); field++) { //why do we have to use -> to accest begin() as if line were a pointer?
         cout << *field << " "; //prints value pointer at current field
      }
      cout << "\n";

   }

}

void csvRead(std::string& fileName, char delimeter, std::vector < std::vector<string> >& csv) { //takes reference of string and csvdata
   std::ifstream is(fileName);
   if (is) {
      int linecount = 1; //holds line Currently being read for printing purposes
      std::string line; //used to process line by line input
      std::vector<std::string> fields; //vector which will be appended to csv upon completetion of line

      while (getline(is, line)) { //read from is into one line per loop

         //auto cr = line.find('\r'); //specify carriage return - zapping carriage return                         
         //if (cr != std::string::npos) line.erase(cr, 1); //remove the carriage return if it is found 

         std::string field;
         for (size_t i = 0; i < line.size(); i++) {

            //loop iteration through the entire line - placed <= as it was skipping last field in a line??

            /*could implement logic to swallow quotes around a field in csv data     
            if (line[i] == '"') {
               field += line[i]; // skip first quote
               for (i++; i < line.size(); i++) {
                  field += line[i]; //second
                  if (line[i] == '"') break;
               }
            }*/
      
            /* Old reading method to trap new lines/delimeters
            if (line[i] == '\n' || line[i] == delimeter) { //why still skip last field when \n is found??
               delSpaces(field); 
               fields.push_back(move(field)); //c++ move field into fields , field then becomes zombie , field is now in a vector of fields
               cout << "Reading Line " << linecount << " , fields Vector currently contains " << fields.size() << (fields.size() > 1 ? " fields" : " field") << " \n";
            }
            else { //read field normally
               field += line[i]; //copy over field data until delim into current field
            }*/

            if (line[i] != delimeter) {
               field += line[i]; //copy over field data until delim into current field
            }

            else {  //it must be a delimeter   
               delSpaces(field); //removes spaces around current field
              
               if (field.size() > 0) { //prevents empty lines from being appened to fields and unto final csv data array
                  //c++ move field into fields , field then becomes zombie , field is now in a vector of fields
                  fields.push_back(move(field));
               }
               
               //cout << "Delimeter found on line " << linecount << " , fields Vector now contains " << fields.size() << " Number of fields \n";
            }

         }//end of for looping through the line

         linecount++;//Since it is now the end of the line, trim and append the final field that has no delimeter at the end of for loop 
         delSpaces(field); //removes spaces around current field
         
         if (field.size() > 0) { //prevent faulty fields from being appended
            fields.push_back(move(field)); //c++ move field into fields , field then becomes zombie , field is now in a vector of fields
            //cout << "CSV Data being pushed back, one final undelimited field has been appended \n";
            csv.push_back(move(fields)); //appending fields to csv
         }

      }//while getline is line is true

      cout << "Completed reading, CSV Vector contains " << csv.size() << " Number of Lines \n";

   }//if input stream is is true

}//csvRead Function closer


bool taskNameValid(string& s) {
   if (s.empty()) { return false; }
   for (auto chr : s) {
      if (!(isalnum(chr) || chr == '_')) return false; // if not alpha , number or underscoere it is not valid
   }
   return true;
}

bool taskSlotValid(string& s) {
   for (auto chr : s) {
      if (!isdigit(chr)) return false; // if not  number its invalid
   }
   return true;
}

//Item Tools here
bool ItemNameValid(string& s) {
   if (s.empty()) { return false; }
   for (auto chr : s) {
      if (!(isalnum(chr) || chr == '_')) return false; // if not alpha , number or underscoere it is not valid
   }
   return true;
}

bool ItemSlotValid(string& s) {
   for (auto chr : s) {
      if (!isdigit(chr)) return false; // if not  number its invalid
   }
   return true;
}

//Order tools here


//BUG REPORT - Previous customer order name "Salt-N-Pepa" was crashing the program, retyped same name and now works? ascii resolution error perhaps?
bool OrderNameValid(string& s) {
   if (s.empty()) { return false; }
   for (auto chr : s) {
      if (!(isalnum(chr) || chr == '_')) return false; // if not alpha , number or underscoere it is not valid
   }
   return true;
}

bool OrderSlotValid(string& s) {
   for (auto chr : s) {
      if (!isdigit(chr)) return false; // if not  number its invalid
   }
   return true;
}
