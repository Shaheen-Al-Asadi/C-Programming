#pragma once
#include <iostream>

namespace sict {

   class Hero {

      //char _name[20]; moved to public , could make a getter to use superhero copy constructor
      //MOVED _STRENGTH TO PUBLIC - reflect hint?

   public:

      char _name[20];

      double _strength;

      Hero();

      Hero(const char* name, double strength);

      void setEmpty();

      //a query that returns true if the object is in a safe empty state; false otherwise.
      bool isEmpty() const;

      //a query that returns the strength of the hero if the hero object is not empty.This query returns 0.0 if the object is empty.
      double getStrength() const;

      //a query that receives a reference to an ostream object and inserts into that object “(the name of the hero) - (strength)” as shown in the example below.If the current object is empty, this function does nothing.
      void display(std::ostream&) const;

      //a member operator that receives a double and reduces the Hero’s strength by the specified amount.If the strength passed in as an argument is greater than the Hero’s strength, then set the Hero’s strength to 0.0.
      void operator -= (double strength);

      //a member operator that receives a double and increases the Hero’s strength by the specified amount.
      void operator += (double strength); 

   };

   //a helper operator that receives references of two objects of Hero, compares their strengths and returns the result as a bool.
   bool operator<(const Hero&, const Hero&);

}
