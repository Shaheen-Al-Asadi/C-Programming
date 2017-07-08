//to use non MS specific strcpy for portability instead of strcpy_s
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Hero.h"
namespace sict {


   void Hero::setEmpty() {
      _name[0] = '\0';
      _strength = 0.0;
   }

   Hero::Hero() {
      _name[0] = '\0';
      _strength = 0.0;
   }

   Hero::Hero( const char* name, double strength) {
      
      if (name != nullptr) {
	      strcpy(_name, name);
      }
      else {
         _name[0] = '\0';
      }

      _strength = strength;
   }

   //a query that returns true if the object is in a safe empty state; false otherwise.
   bool Hero::isEmpty() const {
      
      if ( _strength <= 0) {
         return true;
      }
      else {
         return false;
      }
   }

   //a query that returns the strength of the hero if the hero object is not empty.This query returns 0.0 if the object is empty.
   double Hero::getStrength() const {

      if (!isEmpty()) {
         return _strength;
      }
      else {
         return 0.0;
      }
   }

   //a query that receives a reference to an ostream object and inserts into that object “(the name of the hero) - (strength)” as shown in the example below.If the current object is empty, this function does nothing.
   void Hero::display(std::ostream& os) const {
      if (!isEmpty()) {
         os << _name << " - " << getStrength() << std::endl;
      }
   }

   //a member operator that receives a double and reduces the Hero’s strength by the specified amount.If the strength passed in as an argument is greater than the Hero’s strength, then set the Hero’s strength to 0.0.
   void Hero::operator -= (double strength) {

      if (getStrength() < strength) {
         _strength = 0.0;
      }
      else {
         //_strength = ( _strength - strength); ?
         _strength -= strength; 
      }

   }

   //a member operator that receives a double and increases the Hero’s strength by the specified amount.
   void Hero::operator += (double strength) {
      _strength += strength;
   }

   //a helper operator that receives references of two objects of Hero, compares their strengths and returns the result as a bool.
   bool operator<(const Hero& A , const Hero& B ) {

      return A.getStrength() < B.getStrength();

   }

}

