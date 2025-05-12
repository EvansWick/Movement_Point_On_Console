#include "RealImage.h"
#include "MoveArgs.h"
#include <iostream>
#include <vector>
#include<Windows.h>


std::string GetPixelColor(int cordX, int cordY);
using namespace std;

void goToxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void RealImage::Move(MoveArgs* direct) {
    MoveArgs* To = direct;
    int WIDTH = To->x2 - To->x1 + 3;
    int HEIGHT = To->y2 - To->y1 + 2;
    char cursor = '+';

    if (WIDTH <= 0 || HEIGHT <= 0) {
        cerr << "Помилка: Некоректні розміри поля.\n";
        return;
    }
    // Генерація карти
    
    vector<vector<char>> map(HEIGHT, vector<char>(WIDTH, ' '));
    

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y == 0 || y == HEIGHT - 1) map[y][x] = '#';
        }
        map[y][WIDTH - 2] = '#';
        map[y][0] = '#';
        map[y][WIDTH - 1] = '\n';
    }
    map[To->y][To->x] = cursor;
    // Правильний вивід масиву на консоль: спочатку рядки, потім стовпці
    for (int y = 0; y < HEIGHT; y++) {
        cout << "\t";
        for (int x = 0; x < WIDTH; x++) {
            cout << map[y][x];
        }
        //cout << endl; // Перехід на новий рядок після кожного рядка
    }
    cout << endl << endl << "\tCOORDINATES OF CURSOR: X(" << To->x << ")" << " Y(" << To->y << ")";
    cout << "\n\t" << GetPixelColor(To->x, To->y) << "\n";
    goToxy(0, 0);
}
std::string GetPixelColor(int cordX, int cordY) {
    ostringstream ss;
    ss << "Return color of pixel in point A(" << cordX << ", " << cordY << ")";
    return ss.str();
}