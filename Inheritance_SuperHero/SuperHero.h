#pragma once
#include <iostream>
#include "Hero.h"

namespace sict {

   class SuperHero : public Hero {

      double _multiplier;

   public:

      SuperHero();
      SuperHero(const SuperHero& hero);
      SuperHero(const char* name, double str, double multiplier); //inherted constructor in cpp
      double getStrength();
      void operator *= (SuperHero& Hero);
      void display(std::ostream& os) const;

   };


}