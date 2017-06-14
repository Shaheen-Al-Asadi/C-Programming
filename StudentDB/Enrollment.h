// Date	June 5th 2016
// Author   Shaheen Al-Asadi 013 090 154
/////////////////////////////////////////////////////
#ifndef SICT_ENROLLMENT_H_
#define SICT_ENROLLMENT_H_
#include <iostream>
namespace sict{


   class Enrollment {
   private:
      char name_[31];
      char code_[11];
      int year_; //assumed to be >=2015
      int semester_; //assumed to be >0 and <4
      int slot_; //assumed to be >0 and <6
      bool enrolled_; //false indicates student has withdrawn from the course

   public:
      void display(bool nameOnly = false)const;
      bool isValid()const;
      void setEmpty();
      bool isEnrolled() const;
      bool isEmpty(const char* name, const char* code);
      void set(const char* name, const char* code, int year, int semester, int time, bool enrolled = false);

      bool hasConflict(const Enrollment &other) const;

      Enrollment();
      Enrollment(const char* name, const char* code, int year, int semester, int time);
      ~Enrollment();

    void withdraw();
    int enrol(const Enrollment* enrollments, int size);

  };

}

#endif