#ifndef SICT_CONTACT_H_
#define SICT_CONTACT_H_
#include "PhoneNumber.h"
// Shaheen Al-Asadi 013 090 154 june 17 2016

namespace sict{
  class Contact{

    char name_[41];
    PhoneNumber* phoneNumber_;
    int _noPN;
    void setEmpty();

  public:

    void read();
    void display()const;
    bool isEmpty()const;

    Contact();
    Contact(const char* name, int numPN);
    ~Contact();

    Contact(const Contact& src);
    Contact& operator=(const Contact& C);

  };

}

#endif
