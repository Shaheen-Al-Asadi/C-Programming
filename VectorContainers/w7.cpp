// Workshop 7 - STL Containers
// w7.cpp

#include <iostream>
#include <string>
#include "Sale.h"

int main(int argc, char** argv) {
   
   if (argc != 2) {
      std::cerr << argv[0] << ": incorrect number of arguments\n";
      std::cerr << "Usage: " << argv[0] << " file_name\n";
      return 1;
   }

   //Used for no Command line testing
   std::string str = "Sales.dat";
   const char *cstr = str.c_str();
   //w7::Sale sale(cstr);

   w7::Sale sale(argv[1]); //Any Exceptions should return 2
   sale.display(std::cout);

   std::cout << "\nPress any key to continue ... ";
   std::cin.get();
}

/* Expected Output

Product No      Cost Taxable
10012     34.56
10023     45.67 HST
10234     12.32 PST
10056     67.54
10029     54.12 HST
10034     96.30
Total    324.47

Press any key to continue ...

*/