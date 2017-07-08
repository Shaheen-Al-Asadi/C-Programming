#include <cstring>
#include <iostream>
#include "Contact.h"
#include "PhoneNumber.h"
// Shaheen Al-Asadi 013 090 154 june 17 2016
using namespace std;

namespace sict{

   Contact::~Contact() {
      delete[] phoneNumber_;
      phoneNumber_ = nullptr;
   }

   Contact::Contact() {
      name_[0] = '\0';
      _noPN = 0;
      phoneNumber_ = nullptr;

   }

   Contact::Contact(const char* name, int numPN) {
      phoneNumber_ = nullptr;
      phoneNumber_ = new PhoneNumber[numPN];
      _noPN = numPN;

      if (name != nullptr) {
         strncpy(name_, name, 41);
         name_[40] = '\0'; //document asks for 40 characters, but prof getlines take in 41 so null byte is added early
      }
      else {
         setEmpty(); // if incoming data is invalid, set to safe empty state
      }
   }

  void Contact::display()const{
    //display the name and go to new line
     cout << name_ << endl;

    // loop through elements of phoneNumber_ up to _noPN and display them one by one
     for (int i = 0; i < _noPN; i++)
     {
        phoneNumber_[i].display();
     }

    // draw a 40 char line using '-' and go to new line
     for (int j = 0; j < 40; j++)
     {
        cout << "-";
     }
     cout << endl;

  }

  void Contact::read(){
    cout << "Contact Name: ";
    cin.getline(name_, 41, '\n');
    cout << "Please enter " << _noPN << " phone numbers: " << endl;
    for (int i = 0; i < _noPN; i++){
      cout << i + 1 << ": ";
      phoneNumber_[i].read(); //using another classes functions to perform a contact method using the custom type 
    }
  }



  bool Contact::isEmpty()const{
    return phoneNumber_ == nullptr;
  }

  void Contact::setEmpty(){
    name_[0] = 0;
    _noPN = 0;
    phoneNumber_ = nullptr;
  }


  Contact::Contact(const Contact& src) {
     // could replace all with - this = src ??
     if (src.isEmpty()) {
        setEmpty();
     }
     else{ //if source is not empty, copy resources
     // if src.phoneNumber_ != nullptr
        strcpy(name_, src.name_);
        _noPN = src._noPN;
        phoneNumber_ = new PhoneNumber[src._noPN];

        for (int i = 0; i < src._noPN; i++) {
           phoneNumber_[i] = src.phoneNumber_[i];
        }
     }
  }

  Contact& Contact::operator=(const Contact& C) {

     if ( &C != this) {  // if this object is the source

        delete[] phoneNumber_; //delete array as incoming could be bigger

        if (C.phoneNumber_ != nullptr) { //if incoming is valid data then use copy constructor

         // HOW TO INVOKE COPY CONSTRUCTOR HERE?

         //===== REBUILDING COPY CONSTRUCTOR HERE =====

           if (C.isEmpty()) {
              setEmpty();
           }
           else { //if source is not empty, copy resources
              strcpy(name_, C.name_);
              _noPN = C._noPN;
              phoneNumber_ = new PhoneNumber[C._noPN];

              for (int i = 0; i < C._noPN; i++) {
                 phoneNumber_[i] = C.phoneNumber_[i];
              }
           }
         //===== END OF REBUILD COPY CONSTRUCTOR HERE =====

        }
     }
     return *this; //returns actual object, this returns address of object
  }
}
