#pragma once
#include "order.h"

class Job : public Order {

   vector<bool> installed;

public:

   Job(){};

   Job(Order* o):Order(*o){
      installed.resize( getSize() ); //allocate room for installed vector identical to orderitems vector 
      for (size_t i = 0; i < getSize(); i++) { //getsize from order being called, not manager
         installed[i] = false; //default state
      }
   };

   bool Installed(size_t i){ return installed[i]; }
   void Installed(size_t i, bool value) { installed[i] = value; }

};
