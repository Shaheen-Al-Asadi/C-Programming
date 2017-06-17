#include <iomanip>
#include "Account.h"
#include <cstring>

using namespace std;

namespace sict{

    void Account::display(bool gotoNewline)const{
        cout << (name_[0] ? name_: "No Name") << ": $" << setprecision(2) << fixed << balance_;
        if (gotoNewline) cout << endl;
    }

    //CONSTRUCTORS
    Account::Account(){
        name_[0] = 0;
        balance_ = 0;
    }
    Account::Account(double balance){
        name_[0] = 0;
        balance_ = balance;
    }
    Account::Account(const char name[], double balance){
        strcpy(name_, name);
        balance_ = balance;
    }

    //MEMBER OPERATOR METHODS
    Account& Account::operator+=(const Account& incoming) {
       balance_ += incoming.balance_;
       return *this;
    }

    Account& Account::operator=(const Account& incoming) {

       if (this != &incoming) { //check for self assesment

          if (name_ != nullptr) { //sets current name to empty if not empty
             name_[0] = 0;
          }    

          if (incoming.name_ != nullptr){ //if incoming name exists, copy it over
             strcpy(name_, incoming.name_);
          }

          if (incoming.balance_ != 0) {
             balance_ = incoming.balance_;
          }

       }
       return *this;
    }
    
    //setter getters
    double Account::retBalance() const { //return a const value
       return balance_;
    }

    double Account::setBalance(const double b) {
       balance_ = b;
       return balance_;
    }

    //Helper functions NONFRIEND
    double& operator+=(double& value, const Account& C) {
       value += C.retBalance();
       return value;
    }

    double operator+(double& left, const Account& right) {
       double value;
       value = left + right.retBalance();

       return value;
    }

    std::ostream& operator<<(std::ostream& os, const Account& i) {

       //os << (i.name_[0] ? i.name_ : "No Name") << ": $" << setprecision(2) << fixed << i.balance_;
       i.display(false);
       return os;
    }
   
    Account operator+(const Account& left, const Account& right) {

       Account retParcel;
       retParcel.setBalance(left.retBalance() + right.retBalance());
       return retParcel.retBalance();

    }

}
