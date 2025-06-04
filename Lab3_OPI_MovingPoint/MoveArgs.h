#ifndef MOVEARGS_H
#define MOVEARGS_H
#include <string>
#include <windows.h>

//std::string emptryStr = "                                                                                                                                                   ";

struct MoveArgs {
    int firstGo = 0;
    int wastedObstacles = 0;
    int recordSeconds = 0;
    int gameOver = 0;
    int x = 0;
    int y = 0;
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    DWORD startTime = 0;
};

#endif