#pragma once
#include "task.h"
#include <queue>
#include "job.h"

class Machine : public Task{ //a machine is basically a task

	int inBoundCount; //how many edges point to this node

public:

   queue <Job> inputQ; //a queue of Orders with an Attached "Installed" attribute [ job ]
   bool bInstaller;
   bool bRemover;

   Machine():inBoundCount(0),bInstaller(false),bRemover(false){};//default ctor

   // copies over task fields and creates its own machine instance of those tasks 
   Machine(Task* t):Task(*t),bInstaller(false),bRemover(false),inBoundCount(0){}; 

   bool isSink() { return getTaskAccept().empty(); }; //no pass tasks means its a sink
   bool isSource() { return inBoundCount == 0; }; //if nobody returns to this task it is a source
   bool isSingleton() { return isSink() && isSource(); };
   void incInBoundCount() { inBoundCount++; };
   int getInBoundCount() { return inBoundCount; }
   
   void AddJob(Job j) { inputQ.push(move(j)); }; //adds j job to inputQ - first in first out

   size_t inputQSize() { return inputQ.size(); }

   //returns the first job in inputQ - [front] of line and removes [pop] it from the input q - "finishing a task"
   Job getJob() { Job job = move(inputQ.front()); inputQ.pop(); return move(job); }

   bool isInstaller() { return bInstaller; };
   bool isRemover() { return bRemover; };

   //Classify checks if this machine (task) is an installer / remover by cross refrencing every item in ItemList
   void Classify(ItemManager& im) {
      for (size_t i = 0; i < im.getSize(); i++) {

         if ( getTaskName() == im.getItem(i)->getItemInstaller() ){
            bInstaller = true;
         }
         if ( getTaskName() == im.getItem(i)->getItemRemover() ){
            bRemover = true;
         }
     }
      //if (bInstaller) { cout << getTaskName() << " is an insaller\n"; }
      //if (bRemover) { cout << getTaskName() << " is a remover\n"; }     
   }

};
