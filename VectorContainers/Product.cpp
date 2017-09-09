#include "Product.h"
#include <iomanip>

Product::Product(long number, double cost):pNumber(number),pCost(cost){}

double Product::getCharge() const{
   return pCost;
}

void Product::display(std::ostream & os) const{
   os << std::setw(10) << pNumber //automatically Right alligned 
      << std::setw(10) << std::fixed << std::setprecision(2) << pCost << ' ' << std::endl;

   //The product number and cost occupy fields of width 10. 
   //Note on std::fixed to allign display: c++ reference
   //floating-point values are written using fixed-point notation: the value is represented with
   //exactly as many digits in the decimal part as specified by the precision field (precision) 
}
