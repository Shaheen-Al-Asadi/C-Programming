#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include "item.h"
#include "order.h"
#include "task.h"
#include "machine.h"
#include "job.h"

//slots can be considered as a unit of measurement in a tick tock event simulation
class Factory {

   vector<Machine> machineList; //Machines are really just Tasks

public:

   Factory(ItemManager& im, OrderManager& om, TaskManager& tm) {

      //used to test if input was successful
      //cout << "tm.getSize() = " << tm.getSize() << "\n";

      for (size_t t = 0; t < tm.getSize(); t++) { //for as many tasks in taskList , create a machine
         machineList.push_back( move(Machine ( tm.getTask (t) ) ) );//takes in task* and creates a machine
      }

      //===lambda function
      //take arg of string, and everything is captured by reference , returns a machine* 
      auto MachineFind = [&](std::string& name) -> Machine* {

         for (size_t i = 0; i < machineList.size(); i++) { //for every machine

            if (machineList[i].getTaskName() == name) { //if incoming name matches an existing machine
               return &machineList[i]; //return that reference of that specific machine
            }

         }
         return nullptr; //otherwise not found
      }; 
      //===lambda function

      //finding pass/fail machines and increment their inbound count
      for (auto m : machineList) {
         string pass = m.getTaskAccept();
         //if an accept exists, find that machine and increment an inbound count using its reference
         if (!m.getTaskAccept().empty()) { MachineFind(pass)->incInBoundCount(); } 

         //if a fail exists, find that machine and increment its inbount count
         string fail = m.getTaskFail();
         if (!m.getTaskFail().empty()) { MachineFind(fail)->incInBoundCount(); }
      }

      /*
      cout << "Printing InBoundCount in MachineList...\n";
		//print out inc bound numbers for testing
		for(auto m : machineList) {
			cout << m.getTaskName() << " : " << m.getInBoundCount() <<"\n"; 
		}
      cout << "\n";
      */

      cout << "Identifying Node type...\n";
      int linenumber = 0;
      int source = -1;
      for (size_t m = 0; m < machineList.size(); m++) {
         linenumber++;
         cout << "Machine " << linenumber << ": ";
         cout << machineList[m].getTaskName() << " ";

         if (machineList[m].isSingleton()) {
            cout << "is a Singleton";
         }
         else {

            if (machineList[m].isSource()) {
               cout << "is a Source"; //if no inbound count

               if (source == -1) { // first found source saved , otherwise throw multiple source warning
                  source = m; //returns vector index in machine list of source node
               }
               else {
                  throw string("Multiple sources . fix data and re-submit \n");
               }
            }//if source

         } // else not singleton

         if (machineList[m].isSink()) {
            cout << "is a Sink";
         }//if no pass task, it is a sink

            cout << "\n";

      }//for loop every machine to confirm node/edge type - source, sink , singleton and prints if it is

      //cout << "\nDEBUG : Double Check Nodes are classified correctly Above...";
      //cin.get();

       //step 3 load jobs into input que in source machine
      cout << "Source machine index is MachineList[" << source << "] \n\n";
      if (source == -1) { throw string("No source node. fix data and re-submit \n"); }

      //for every order in order manager, create a machinelist of jobs on a que
      for (size_t i = 0; i < om.getSize(); i++) {
         machineList[source].AddJob( move( Job( om.getOrder(i) )));
      }

      //Optional debug print statement to list number of jobs per machine - only source node ever has jobs [n] times orders
      linenumber = 1; //reseting line number for printing
      for (auto m : machineList) {
         cout << "Machine " << linenumber << ": " << m.getTaskName() << " has " << m.inputQSize() << " Jobs\n";
         linenumber++;
      } //only source node has n number of jobs, where n is the number of orders
      

      //Used for Testing 
      cout << "Classifying Task Roles" << endl;
      for (auto &m : machineList) {
         m.Classify(im);
      }
      
      cout << endl;

      cout << "MachineList Job Queue filled - Starting Time loop...\n\n";

      // --- >> Time Loop Begins
      int time = 0;
      while (true) {
         bool AllDone = true;
         cout << "Starting Time: " << time << "\n";

         //any machine that has something in input que, jobs only begin at source but will move along machine line
         for (auto m : machineList) {
            if (m.inputQSize()) { // has jobs?
               AllDone = false;
               break; //exit loop if found
            }
         } //check if jobs exit in mlist, otherwise jobs finished

         if (AllDone) { 
            cout << "No jobs found in Machine list.\n";
            break;
         }
         else {
            cout << "There are jobs in machine list.\n";
         }

         //Machine loop
         for (auto m : machineList) {
            if (m.inputQSize() == 0) { // no more jobs? exit loop back into while loop
               continue;
            }
            //otherwise there is something to do;
            //Job job; //redefinition error previously
            Job job = move(m.getJob()); //pop off first job in que - ( bus line )
            cout << "Machine " << m.getTaskName() << " will work on Job: " << job.getOrderName() << " Product: " << job.getOrderProduct() << "\n";

            if ( m.isSink() ) { // is current working machine a sink? means job about to be finished - simulation over
               cout << job.getOrderName() << "/" << job.getOrderProduct() << " is done!\n";
               continue; // go process next machine's job
            }

            //Step 10 - prep
            bool didSomething = false;

            if (m.isInstaller()) {
               cout << m.getTaskName() << " is an Installer.\n";

               //for each item in orderitems, if installer name is our name then install item using installer func
               for (size_t i = 0; i < job.getSize(); i++) {
                  if (job.Installed(i)) { //already installed
                     continue;
                  }

                  string itemName = job.getItem(i);
                  Item* itemPtr = im.ItemFind(itemName);
                  if (m.getTaskName() == itemPtr->getItemInstaller()) {
                     didSomething = true;
                     time = time + stoi(m.getTaskSlot());//increment time by slots
                     job.Installed(i) == true; //set this item to installed
                     cout << m.getTaskName() << " installed " << itemName << "\n";
                     break; //done installed 1 item
                  }
               }
            }

            if (m.isRemover()) {

               cout << m.getTaskName() << " is a Remover. \n";

               for (size_t i = job.getSize()-1; i > 0 ; i--) { //-- because your removing
                  if (!job.Installed(i)) { //already removed
                     continue;
                  }
                  string itemName = job.getItem(i);
                  Item* itemPtr = im.ItemFind(itemName);
                  if (m.getTaskName() == itemPtr->getItemRemover()) {
                     didSomething = true;
                     time = time + stoi(m.getTaskSlot());//increment time by slots
                     job.Installed(i) == false; //set this item to removed
                     cout << m.getTaskName() << " removed " << itemName << "\n";
                     break; //done removing one item
                  }
               }
            }

            //lambda function that moves a job to its pass/fail destination when called
            auto MovePass = [&] {
               string pass = m.getTaskAccept();
               cout << "Moving job to pass machine " << pass << "\n";
               for (auto &m2 : machineList) {
                  if (m2.getTaskName() == pass) {
                     m2.AddJob(job); // moving to next destination here
                        break;
                  }
               }
            };

            auto MoveFail = [&] {
               string fail = m.getTaskFail();
               cout << "Moving job to fail machine " << fail << "\n";
               for (auto &m2 : machineList) {
                  if (m2.getTaskName() == fail) {
                     m2.AddJob(job);
                     break;
                  }
               }
            };

            if (!didSomething) { //if an installer/remover hasnt acted
               //cout << "!didsomething\n";
               MovePass();       //move job to passed inputq
               continue;         //end of this machine
            }

            if (m.getTaskFail().empty()) { // if there is only a pass task, movepass
               //cout << "Empty fail task\n";
               MovePass();  
               continue;
            }

            //flip coin , & test if odd , pass machine - set to 100% for testing
            if(rand() % 1 + 1 ){ //generates a random number between 0 and 1
               //cout << "Randomizer Passed\n";
               MovePass(); // passed
               continue;
            }
            else {
               //failed rand
               //cout << "Randomizer Failed\n";
               MoveFail();
            }

         } //Working on jobs in mlist loop

         cout << "Simulation Over, Total Time: " << time << "\n";
         cin.get();
         exit(99);

      }// end of time loop
   }// factory ctor

   void printMachines() {
      for (auto m : machineList) {
         m.TaskPrint(); 
         //Calls taskPrint from machine as it were a task, only prints if machine copy constructor was used on a task*
      }
   }


};
