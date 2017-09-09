#pragma once
#include "iProduct.h"
#include <vector>

using namespace std;

namespace w7{

   class Sale{

      //Since the products are polymorphic objects, your class stores and accesses them through a set of pointers to the objects.
      vector<w7::iProduct*> products; // holds a vector of iProduct pointers for polymorphic behaviour - KEY LESSON THIS WORKSHOP

   public:

      Sale(const char* fileName);
      void display(ostream& os) const;

   };
}