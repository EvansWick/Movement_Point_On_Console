#ifndef RealImage_h
#define RealImage_h

#include "Subject.h"
#include <string> 
#include <sstream>
#include <vector>
#include<Windows.h>

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // Для Visual Studio
using namespace irrklang;

class ProxyRealImage;

class RealImage : public Subject {

 public:
     void goToxy(int x, int y);
     void Move(MoveArgs* direct) override;
     RealImage(MoveArgs* direct);
     std::vector<std::pair<int, int>> obstacles;
     void setCounter(int count);
 private:
     MoveArgs* ToForFunctions;
     int tickCounter = 0; // рахує цикли для генерації
     void generateObstacle(int width);
     void moveObstacles();
     bool checkCollision(int playerX, int playerY);
};

#endif // RealImage_h
