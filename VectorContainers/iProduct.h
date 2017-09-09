#ifndef _I_PRODUCT_H_
#define _I_PRODUCT_H_

// Workshop 7 - STL Containers
// iProduct.h


//IPRODUCT IS AN ABSTRACT CLASS , controls structure and needed methods for product and taxable product, to be used as a pointer 
//to access polymorphic container in sale vector<iProduct*> products;

#include <iostream>
#include <fstream>

namespace w7 {

   class iProduct {
   public:
      virtual double getCharge() const = 0; //pure virtual functions to be implemented in derived objects
      virtual void display(std::ostream&) const = 0;
   };

   //This promises the compiler that these functions will exist somewhere - Sale.cpp
   std::ostream& operator<<(std::ostream&, const iProduct&); //basically calls a iproduct display given an os reference for" << potatoe"
   iProduct* readProduct(std::ifstream&); //reads one record at a time

}
#endif