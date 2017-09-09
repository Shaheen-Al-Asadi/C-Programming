#include "TaxableProduct.h"
#include <iomanip>

//Initialize members including product obj
TaxableProduct::TaxableProduct(long number, double cost, char taxType ):Product(number, cost), taxType(taxType){}

double TaxableProduct::getCharge() const{
   return ( pCost * (taxType == 'H' ? taxes[0] : taxes[1]) ); //returns 1.13 if true, otherwise 1.08 
}

void TaxableProduct::display(std::ostream& os) const{
   os << std::setw(10) << pNumber
      << std::setw(10) << std::fixed << std::setprecision(2) << pCost
      << ' ' << (taxType == 'H' ? "HST" : "PST") << std::endl;
   //seperate from product object, wont print PST on default as not using this method
}

