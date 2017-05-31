#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <iostream>
using namespace std;

class Exception{
  private:
  string description;

  public:
  
  Exception();
  Exception(const char* desc);
  Exception(string desc);
  string getDescription() const;
};

ostream& operator<<(ostream& out,const Exception& e);

#endif
