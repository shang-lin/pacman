#include "Exception.h"

Exception::Exception(){
  description = string("");
}

Exception::Exception(const char* desc){
  description = string(desc);
}

Exception::Exception(string desc){
  description = desc;
}

string Exception::getDescription() const {
  return description;
}

ostream& operator<<(ostream& out,const Exception& e){
  out << e.getDescription();
  return out;
}
