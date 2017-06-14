//Version: 1.1
//      1.1: replaced all IsinValids to Invalid
// Date	June 5th 2016
// Author   Shaheen Al-Asadi 013 090 154
/////////////////////////////////////////////////////
using namespace std;
#include <iostream>
#include "Enrollment.h"
#include <cstring>
namespace sict {

   //add validation for isvalid?
  
   bool Enrollment::isValid()const {
      return name_ && name_[0];
   }


   void Enrollment::setEmpty() {
      name_[0] = 0;
      code_[0] = 0;
      year_ = 0;
      semester_ = 0;
      slot_ = 0;
      enrolled_ = false;
   }

   bool Enrollment::isEmpty(const char* name, const char* code) {
      return (name != NULL && name[0] != 0) && (code != NULL && code[0] != 0);
   }

   bool Enrollment::isEnrolled() const {
      return enrolled_;
   }


   void Enrollment::display(bool nameOnly)const {
      if (isValid()) {
         cout << name_;
         if (!nameOnly) {
            cout << endl << code_ << ", Year: " << year_ << " semester: " << semester_ << " Slot: " << slot_ << endl;
            cout << "Status: " << (isEnrolled() ? "E" : "Not e") << "nrolled." << endl;
         }
      }
      else {
         cout << "Invalid enrollment!" << endl;
      }
   }

   //code[0] and name[0] is to indicate that no empty string is entered - also what happens to "" in set input? ignored?
   void Enrollment::set(const char* name, const char* code, int year, int semester, int time, bool enrolled) {
      if (name != nullptr && code != nullptr && code[0] && name[0] && year >= 2015 && semester > 0 && semester < 4 && time > 0 && time < 6) {
         strncpy(name_, name, 31);
         strncpy(code_, code, 10);
         year_ = year;
         semester_ = semester;
         slot_ = time;
         enrolled_ = enrolled;
      }
      else {
         setEmpty();
      }
   }

   bool Enrollment::hasConflict(const Enrollment &other) const {
      if (other.year_ != 0 && other.semester_ != 0 && other.slot_ != 0) {
         if (other.year_ == year_ && other.semester_ == semester_&& other.slot_ == slot_) {
         }
         return true;
      }
      else {
         return false;
      }
   }

   Enrollment::Enrollment() {
      setEmpty();
   }


   Enrollment::Enrollment(const char* name, const char* code, int year, int semester, int time) {

      set(name, code, year, semester, time);
   }

   Enrollment::~Enrollment() {
   }


   void Enrollment::withdraw() {
      enrolled_ = false;
   }


   int Enrollment::enrol(const Enrollment* enrollments, int size) {

      for (int i = 0; i < size; i++) {
         if (enrollments[i].year_ == year_ && enrollments[i].semester_ == semester_ && enrollments[i].slot_ == slot_) {
            enrolled_ = false;
            return i + 1;
         }
      }
      enrolled_ = true;
      return 0;
   }


}
