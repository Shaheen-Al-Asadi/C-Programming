#ifndef SICT_ACCOUNT_H__
#define SICT_ACCOUNT_H__

#include <iostream>

namespace sict{

   class Account {
      char name_[41];
      double balance_;

   public:

      void display(bool gotoNewline = true)const;

      //constructors
      Account();
      Account(double balance);
      Account(const char name[], double balance = 0.0);

      //specifying member operator overloads
      Account& operator+=(const Account& incoming);
      Account& operator=(const Account& incoming);

      //setter getters to prevent friend methods and exposing member variables
      double retBalance() const ;
      double setBalance(const double b);

   };


   double operator+(double& left, const Account& right);
   Account operator+(const Account& left, const Account& right);
   double& operator+=(double& value, const Account& C);
   std::ostream& operator<<(std::ostream& os, const Account& i);

};


#endif
