#ifndef ProxyRealImage_h
#define ProxyRealImage_h

#include "Subject.h"
#include "MoveArgs.h"


class RealImage;

class ProxyRealImage : public Subject {

 public:
     void Move(MoveArgs* direct) override;

 public:
    int MaxX;
    int MinX;
    int MaxY;
    int MinY;
    int X, Y;

 public:

    /**
     * @element-type RealImage
     */
    RealImage *myRealImage;

    void SetObjectRealImage(RealImage* obj);
};

#endif // ProxyRealImage_h
