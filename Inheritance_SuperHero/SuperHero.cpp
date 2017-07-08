//to use non MS specific strcpy for portability instead of strcpy_s
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Hero.h"
#include "SuperHero.h"
namespace sict {

   SuperHero::SuperHero() : Hero(){
      //using hero no arg constructor 
      _multiplier = 0;
   }

   //how to test for invalid input before base class constructor goes off?
   SuperHero::SuperHero(const char* name, double str, double multiplier): Hero(name, str) {
      _multiplier = multiplier;
   }

   SuperHero::SuperHero(const SuperHero& hero) {
   
      //if hero has < 0 strength (( SHOULD I CHECK IF NAME IS EMPTY/NULLPTR?
      if (hero.isEmpty()) {

         //sets empty using Hero set Empty NEW FUNCTION
         //set name to null and str to zero
         // _name[0] = '\0';
         // _strength = 0;
         setEmpty();

         _multiplier = 0;
      }
      else {

         //need to make setters/getters? why not said in workshop.doc
         strcpy(_name, hero._name);

         _strength = hero._strength;

         _multiplier = hero._multiplier;

      }
   }


   double  SuperHero::getStrength() {

      return ( _multiplier * Hero::getStrength() );

   }

   void  SuperHero::operator *= (SuperHero& iHero) {
      if (getStrength() > iHero.getStrength() ) {
         _strength += iHero.Hero::getStrength(); 
         iHero._multiplier = 0.0; // maybe not needed?
         iHero.setEmpty(); // SetEmpty is new function in Hero 
      }
      else {
         iHero._strength += Hero::getStrength(); //increase winning hero base strength using this objects hero str method
         _multiplier = 0.0;
         setEmpty();
      }
   }
   void  SuperHero::display(std::ostream& os) const {

      //if SuperHero object has < 0 STR
      if (isEmpty()) {
         os << "deceased superhero!" << std::endl;
      }
      else {
         os << "living superhero! ";
         Hero::display(os); //display function has endl included
      }

   }
}