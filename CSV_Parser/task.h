#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

using namespace std;

class Task{

   string taskName, taskSlots, taskAccept, taskFail; 

public:

	Task(){};
   Task(vector<string>& row);
   ~Task() {};

   void TaskPrint();
   void TaskGraph(fstream& os);

   std::string& getTaskName() { return taskName; }; // very efficient use on inline
   std::string& getTaskAccept() { return taskAccept; };
   std::string& getTaskFail() { return taskFail; };
   std::string& getTaskSlot() { return taskSlots; };

};

class TaskManager {

   vector<Task> taskList;

public:

   TaskManager(std::vector <std::vector<std::string> >& csv);

   ~TaskManager();

   void TaskPrint();

   void TaskGraph(string& filename);

   //MS4 function loops through tasklist and returns if it finds a task with that name
   Task* TaskFind(std::string name);

   //Checks using Taskfind if a task's pass/fail fields exist as their own seperate task within task list
   void IntegrityCheck(bool& ok);
   size_t getSize() { return taskList.size(); };
   Task* getTask(size_t i) { return &taskList[i]; };// returns a reference to a specific task in the vector


}; //task manager

