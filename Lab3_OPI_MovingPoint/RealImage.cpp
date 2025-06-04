#include "RealImage.h"
#include "MoveArgs.h"
#include <iostream>
#include <vector>


ISoundEngine* engine = createIrrKlangDevice();
ISound* Vidlic = engine->play2D("bah.wav", false, true, true);

using namespace std;

RealImage::RealImage(MoveArgs* direct)
{
    ToForFunctions = direct;
}

void RealImage::setCounter(int count) {
    this->tickCounter = count;
}

void RealImage::goToxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

//Функції для перешкод
void RealImage::generateObstacle(int width) {
    // Випадкова позиція перешкоди зверху
    int x = rand() % (width - 2) + 1; // не на краях
    this->obstacles.push_back({ x, 0 });
    if (tickCounter > 30) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
    if (tickCounter > 50) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
    if (tickCounter > 70) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
    if (tickCounter > 90) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
    if (tickCounter > 110) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
    if (tickCounter > 1300) {
        int x = rand() % (width - 2) + 1; // не на краях
        this->obstacles.push_back({ x, 0 });
    }
}

void RealImage::moveObstacles() {
    for (auto& obs : obstacles) {
        obs.second++; // рух вниз
    }
    // Видаляємо ті, що вийшли за межі
    for (int i = 0; i < obstacles.size(); ) {
        if (obstacles[i].second > 30) { //////////////////////Поле буде статичне. 30х30
            obstacles.erase(obstacles.begin() + i);
            this->ToForFunctions->wastedObstacles++;
            
        }
        else {
            ++i;
        }
    }
}



bool RealImage::checkCollision(int playerX, int playerY) {
    for (const auto& obs : obstacles) {
        if (obs.first == playerX && obs.second == playerY) {
            return true;
        }
    }
    return false;
}



void RealImage::Move(MoveArgs* direct) {
    MoveArgs* To = direct;
    int WIDTH = To->x2 - To->x1 + 3;
    int HEIGHT = To->y2 - To->y1 + 2;
    char cursor = char(219);

    if (WIDTH <= 0 || HEIGHT <= 0) {
        cerr << "Помилка: Некоректні розміри поля.\n";
        return;
    }
    // Генерація карти
    vector<vector<char>> map(HEIGHT, vector<char>(WIDTH, ' '));
    
    // перешкоди
    // Кожен тік гри:
    tickCounter++;
    if (tickCounter % 10 == 0) {
        generateObstacle(WIDTH - 1); // ширина без країв
    }
    moveObstacles();
    if (checkCollision(To->x, To->y)) {
        To->gameOver = 1;
        //To->firstGo = 0;
    }

    // Малюємо перешкоди
    for (const auto& obs : obstacles) {
        if (obs.second >= 0 && obs.second < HEIGHT)
            map[obs.second][obs.first] = 'X';
    }

    //// Відлік
    if (To->firstGo == 0) {
        for (int k = 3; k > 0; k--) {
            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    if (y == 0 || y == HEIGHT - 1) map[y][x] = '#';
                }
                map[y][WIDTH - 2] = '#';
                map[y][0] = '#';
                map[y][WIDTH - 1] = '\n';
            }
            map[To->y][To->x] = '0' + k;
            // Правильний вивід масиву на консоль: спочатку рядки, потім стовпці
            for (int y = 0; y < HEIGHT; y++) {
                cout << "\t";
                for (int x = 0; x < WIDTH; x++) {
                    cout << map[y][x];
                }
                //cout << endl; // Перехід на новий рядок після кожного рядка
            }
            int a = 1000;
            Vidlic = engine->play2D("bah.wav", false, false, true);
            goToxy(0, 0);
            Sleep(a);
        }
        To->firstGo = 1;
    }
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
    goToxy(0, 0);
}