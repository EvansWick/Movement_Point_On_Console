#ifndef Subject_h
#define Subject_h


#include "MoveArgs.h"
#include <string>

class Subject {

 public:
    //virtual std::string GetPixelColor(int cordX, int cordY) = 0;
    virtual void Move(MoveArgs* direct) = 0;

public:
    // virtual destructor for interface 
    virtual ~Subject() { }
};

#endif // Subject_h
