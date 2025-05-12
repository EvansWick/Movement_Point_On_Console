#ifndef RealImage_h
#define RealImage_h

#include "Subject.h"
#include <string> 
#include <sstream>

class ProxyRealImage;

class RealImage : public Subject {

 public:

     void Move(MoveArgs* direct) override;

 public:

};

#endif // RealImage_h
