#include "ProxyRealImage.h"
#include "RealImage.h"


void ProxyRealImage::Move(MoveArgs* direct)
{
	MoveArgs* To = direct;

	if (To->y <= 0) To->y = 1;
	if (To->y >= (To->y2 - To->y1)) To->y = (To->y2 - To->y1);
	if (To->x <= 0) To->x = 1;
	if (To->x >= (To->x2 - To->x1)) To->x = (To->x2 - To->x1);

	myRealImage->Move(To);
	
}

void ProxyRealImage::SetObjectRealImage(RealImage* obj) { // Привязка до об'єкта
	this->myRealImage = obj;
}
