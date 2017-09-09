#pragma once

#include "Product.h"

//only iproduct and sale is in namespace w7 atm, everything else is default

class TaxableProduct : public Product{

   //The same tax rates apply to all TaxableProduct objects.  Use a class array (an array of class variables) 
   //to store the tax rates for HST and PST tax codes (13% and 8%).  
   //Inherits pNumber and pCost from Product as members
   double taxes[2] = { 1.13, 1.08 }; // AKA Class Array
   char taxType;

public:

   TaxableProduct(long number, double cost, char tax);
   double getCharge() const;
   void display(std::ostream& os) const;
};