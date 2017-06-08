#pragma once
#include "util.h"
#include "task.h"
#include "item.h"
#include "order.h"
#include "factory.h"
#include "Job.h"
#include "Machine.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility> //move
#include <algorithm> //for delSpaces function

//Keep it simple, baby steps, always be prepared to show your boss something
using namespace std;

int main(int argc, char *argv[]) {

   try {
      //REMEMBER TO UNCOMMENT THIS
      if (argc != 5) { throw string("Usage: ") + argv[0] + " itemFile.dat orderFile.dat taskFile.dat Delimeter \n"; }

      //Default Test Files
      //std::string filenameItem  = "ItemList.dat"; //argv[1]; //1st argument after program call
      //std::string filenameOrder = "CustomerOrders.dat"; //argv[2];
      //std::string filenameTask  = "TaskList.dat"; //argv[3];

      //Store incoming file name
      std::string filenameItem = argv[1]; //1st argument after program call
      std::string filenameOrder = argv[2];
      std::string filenameTask = argv[3];

      char delimeter = argv[4][0]; //4th arg, 1st character 

      cout << "-==========================================================-\n";
      cout << "Milestone 5 is running files: \n" << filenameItem << "\n" << filenameOrder << "\n" << filenameTask << "\nUsing delimeter --> " << delimeter << " <-- \n\n";

      //std::vector < std::vector<string> > csvData; //creates 2d ragged array: csvData[line][field], ragged arrays can be of dynamic size and not always rectangular
      std::vector < std::vector<string> > csvItemData;
      std::vector < std::vector<string> > csvOrderData;
      std::vector < std::vector<string> > csvTaskData;

      //csvRead(fileIn, delimeter, csvData); //custom function to read CSV Data 
      cout << "Reading ItemData: ";
      csvRead(filenameItem, delimeter, csvItemData); 
      cout << "Reading OrderData: ";
      csvRead(filenameOrder, delimeter, csvOrderData);
      cout << "Reading TaskData: ";
      csvRead(filenameTask, delimeter, csvTaskData);

      //initializing seperate outgoing file names , removing .dat from incoming filename to do so
      std::string fileOutItem = filenameItem.substr(0, (filenameItem.size() - 4));
      std::string fileOutOrder = filenameOrder.substr(0, (filenameOrder.size() - 4));
      std::string fileOutTask = filenameTask.substr(0, (filenameTask.size() - 4));

      bool GoodtoGo = true; //Will only create factory if integrity checks passed

      //Task Manager Initialization 
      cout << "\nCreating Task Manager \n";
      TaskManager tm(csvTaskData);
      //cout << "\nCalling Task Manager Print: \n";
      //tm.TaskPrint();
      cout << "Creating Graph: " << fileOutTask << ".gv\n";
      tm.TaskGraph(fileOutTask);
      cout << "Running Task Manager Integrity check\n\n";
      tm.IntegrityCheck(GoodtoGo);

      //Item Manager Initialization
      cout << "Creating Item Manager Object\n";
      ItemManager im(csvItemData);
      //cout << "\nCalling Item Manager Print: \n";
      //im.ItemPrint();
      cout << "Creating Graph: " << fileOutItem << ".gv\n";
      im.ItemGraph(fileOutItem);
      cout << "Running Item Manager Integrity check\n\n";
      im.IntegrityCheck(tm , GoodtoGo);

      //Order Manager Initialization
      cout << "Creating Order Manager Object\n";
      OrderManager om(csvOrderData);//will take csv item data to compare that items are in stock
     // cout << "\nCalling Order Manager Print: \n";
      //om.OrderPrint();
      cout << "Creating Graph: " << fileOutOrder << ".gv\n";
      om.OrderGraph(fileOutOrder);
      cout << "Running Order Manager Integrity check\n\n";
      om.IntegrityCheck(im);
      

      if (GoodtoGo == true) {
         cout << "Integrity Checks passed\n";
         cout << "\nCreating Factory using [im, om, tm]...\n\n";
         Factory(im, om, tm);
      }else {
         cout << "Failure to pass one or more Integrity Checks, Resubmit Correct Data\n";
      }

   }
   catch (string& e) {
      cerr << e << "\n";
   }

   cout << "\n ---  Main Completed, Returning 0  --- " << endl;
   std::cin.get();
   //system("pause"); //Comment for non windows users
   return 0;
}


