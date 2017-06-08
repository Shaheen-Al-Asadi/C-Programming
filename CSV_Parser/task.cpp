#pragma once
#include <iostream>
#include "task.h"
#include "util.h" 

Task::Task(vector<string>& row){ //default slot

   try {

      switch (row.size()) { // check if row size at least 4 fields big?

      case 4: //if 4 tasks are in a row, the 4th is the taskfail 
         if (taskNameValid(row[3]))
            taskFail = row[3];
         else
            throw string("expected fail task name, found ") + row[3];

      case 3: //if name valid repeat same func
         if (taskNameValid(row[2]))
            taskAccept = row[2];
         else
            throw string("expected Accept task name, found ") + row[3];

      case 2: //if task slot valid, else throw
         if (taskSlotValid(row[1]))
            taskSlots = row[1];
         else
            throw string("expected slot task number, found ") + row[3];

      case 1: // if name valid, else throw string
         if (taskNameValid(row[0]))
            taskName = row[0];
         else
            throw string("expected task name, found ") + row[3];

         break;

      default:
         throw string("expected 4 fields, found") + to_string(row.size());
      }//switch

   }
   catch (string& error) {
      cout << "Error: " << error << endl;
   }

}//Task Constructor

void Task::TaskPrint() {
   cout << "Name: " << taskName << " > ";
   cout << "Slot: " << taskSlots << " > ";
   cout << "Pass: " << taskAccept << " > ";
   cout << "Fail: " << taskFail << " > ";
}

void Task::TaskGraph(fstream& os) {
   
   if (!taskAccept.empty()) {
      os << taskName << "->" << taskAccept << "[color=green];\n";
   }

   if (!taskFail.empty()) { //minimum requirement is that a name exists
      os << taskName << "->" << taskFail << " [color=red];\n";
   }

   if (taskFail.empty() && taskAccept.empty()) {
      os << taskName << "[shape=box];\n";
   }
}

//Task manager

TaskManager::TaskManager(std::vector <std::vector<std::string> >& csv) {
   int lineNumber = 0;
   for (auto row : csv) {
      try {
         lineNumber++; // to detect errors    
         //cout << "Attempting to create Task: " << lineNumber << endl;
         taskList.push_back(move(Task(row)));
      }
      catch (string& e) {
         cerr << e << "error in line " << lineNumber << "\n";
      }
   }
}

TaskManager::~TaskManager() {}

void TaskManager::TaskPrint() {
   int taskNumber = 0;
   for (auto t : taskList) {
      taskNumber++;
      cout << "Task " << taskNumber << " ";
      t.TaskPrint();
      cout << "\n"; //Not placed here intially, more readable
   }
}

void TaskManager::TaskGraph(string& filename) {
   fstream os(filename + ".gv", ios::out);
   os << "digraph DG {\n";

   for (auto t : taskList) {
      t.TaskGraph(os);
   }

   os << "};\n";
   os.close();
   //string cmd = string("dot - Tpng ") + filename + ".gv >" + filename + ".gv.png";
   //system(cmd.c_str); // for graph wizz api your using later
}

//MS4 function loops through tasklist and returns if it finds a task with that name
Task* TaskManager::TaskFind(std::string name){ 
	for (size_t i = 0; i < taskList.size(); i++) {
		if (taskList[i].getTaskName() == name) {
			return &taskList[i];
		}
	}
	return nullptr; //not found
};

//Compares every task in task list and makes sure reference of taskPass and Taskfail have their own tasks
//ie if you say go to cpu if motherboard passes, it checks to see if cpu exists as its own task, and it checks if reinstall motherboard task exists
void TaskManager::IntegrityCheck(bool& ok) {

   try {
      for (auto t : taskList) {
         if (!t.getTaskAccept().empty() && TaskFind(t.getTaskAccept()) == nullptr) {
            ok = false;
            throw string("Task '") + t.getTaskName() + "' referenced Pass Task '" + t.getTaskAccept() + "' but it does not exist\n";
         }

         if (!t.getTaskFail().empty() && TaskFind(t.getTaskFail()) == nullptr) {
            ok = false;
            throw string("Task ") + t.getTaskName() + "' referenced Fail Task '" + t.getTaskFail() + "' but it does not exist\n";
         }
      }
   }
   catch (string& e) { cout << "Error: " << e << "\n"; }
}
