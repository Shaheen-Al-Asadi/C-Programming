
#include "Sale.h"
#include "TaxableProduct.h"
#include <iomanip>
#include <vector>
#include <string>
#include <sstream> //for read product string stream conversion

using namespace std;
using namespace w7;

// copies the product information into an STL container.  
Sale::Sale(const char* fileName){ 
   
   ifstream ifs(fileName);
   iProduct* currentP;

   // if not EOF , or empty product, pushback - calls read product and creates non tax/tax product into currentP
   while (ifs.good() && (currentP = readProduct(ifs)) != nullptr) { //readProduct was declared in iProduct as virtual pure function
      products.push_back(currentP);
   }
}

//The product number and cost occupy fields of width 10. 
void Sale::display(ostream& os) const{

   os << setw(10) << "Product No" << setw(10) << "Cost" << " " << "Taxable" << endl;
   double totalAmt= 0;

   for (auto currentP : products){ //For every product in vector
      //os << currentP; //to use << operator leads to errors - use pointer call method
      currentP->display(os); //pointer call to respective derived display function
      totalAmt += currentP->getCharge(); //pointer call to respective derived tax calculator, product only returns base cost
   }

   os << setw(10) << "Total" << fixed << setprecision(2) << setw(10) << totalAmt << endl;
}

//calls respective product display , declared in iproduct and implemented in sale , not in use anywhere, sale display uses pointer call and never a direct product yet
ostream& w7::operator<<(ostream& os, const iProduct& item){
   item.display(os);
   return os;
}


//declared in iproduct , used to construct product and tax products into product vector container in sale 
iProduct* w7::readProduct(ifstream& is){

   string line;
   getline(is, line);
   stringstream ss;

   //return product for push back || nullptr
   if ( !line.empty() ) {

      ss.str(line); // ss is now a copy of line

      //hold product attributes
      vector<string> attributes;

      //seperate line into seperate attributes
      string buffer;
      while (ss >> buffer) { //get line until space from stringstream "entire string" into one buffer word
         attributes.push_back(buffer);
      }

      iProduct* product; //nullptr on declaration

      if (attributes.size() == 3) { //If there is a tax column in this line
         product = new TaxableProduct( stol(attributes[0]), stod(attributes[1]), attributes[2].c_str()[0]); //string to char for tax type
      }
      else {
         product = new Product(stol(attributes[0]), stod(attributes[1]));
      }// stol string to long for pNumber , stod string to double for cost and tax type

      return product; //possible this will return a nullptr?

   }//If line is not empty, otherwise return nullptr
   else {
      return nullptr;
   }
}

//Segfaults are caused by a program trying to read or write an illegal memory location