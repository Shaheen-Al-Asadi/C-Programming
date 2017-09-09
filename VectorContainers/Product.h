#pragma once
#include "iProduct.h"

class Product : public w7::iProduct{

protected: //To add accesibility to derived classes
   long pNumber; //long to store large product number digit
   double pCost;

public:
   Product(long number, double cost);
   double getCharge() const;
   void display(std::ostream& os) const;
};
