#include <conio.h>     // для _kbhit() і _getch()
#include <windows.h>   // для Sleep()
#include "MoveArgs.h"
#include "RealImage.h"
#include "ProxyRealImage.h"
#include <iostream>
#include <algorithm> //Для макс вектора
#include <mmsystem.h> // Для музики


using namespace std;

int main() {

    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine) return 1;
    ISound* SoundOnTrack = engine->play2D("C:/Users/ivanm/source/CURSACH_Gonki/Debug/MusicOnTrack.wav", true, false, true);
    ISound* SoundMenu = engine->play2D("st.wav", true, false, true);
    ISound* SoundFeil = engine->play2D("feil.wav", false, true, true);
    ISound* SoundEnter = engine->play2D("Enter.wav", false, true, true);
    ISound* SoundCountingScore = engine->play2D("Enter.wav", false, true, true);
    ISound* SoundDriving = engine->play2D("Driving.wav", false, true, true);
    ISound* SoundPunctUp = engine->play2D("punct.wav", false, false, true);// зациклений, але ПАУЗА (true, true)
    //engine->play2D("C:/Users/ivanm/source/CURSACH_Gonki/Debug/st.wav", false); // false — не повторять
    system("cls");
    //system("pause");

    
   
    
    MoveArgs moveArgs;
    moveArgs.x1 = 0;
    moveArgs.x2 = 15;
    moveArgs.y1 = 0;
    moveArgs.y2 = 30;
    moveArgs.x = (moveArgs.x2 + moveArgs.x1) / 2;
    moveArgs.y = (moveArgs.y2 + moveArgs.y1) / 2;

    int currentTime = 0;
    vector<int> SpeedResults(1, 0);

    RealImage real(&moveArgs);
    ProxyRealImage proxy;
    proxy.SetObjectRealImage(&real);

	while (true)
	{
        int sessionGames = 0;
        int totalPlayTime = 0;


        while (true) {
            int selectedIndex = 0; // 0 = Play, 1 = Statistic
            bool menuRunning = true;

            while (menuRunning) {
                system("cls");

                // Створимо просту рамку
                for (int i = 0; i < 9; i++) {
                    cout << "\n\t";
                    for (int j = 0; j < 22; j++) {
                        if (i == 0 || i == 8 || j == 0 || j == 21)
                            cout << "#";
                        else
                            cout << " ";
                    }
                    
                }

                // Центр меню, 2 пункти
                string options[3] = { "\tPlay", "Statistic", "\tQuit"};
                for (int i = 0; i < 3; i++) {
                    int line = 2 + i * 2; // на 2-му та 4-му рядку
                    COORD pos = { 3, (SHORT)line };
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

                    if (i == selectedIndex)
                        cout << "\t#### " << options[i] << "\t ####";
                    else
                        cout << "    " << options[i];
                }

                char key = _getch();
                if (key == 'w' && selectedIndex > 0) {
                    selectedIndex--;
                    SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                }
                else if (key == 's' && selectedIndex < 2) {
                    selectedIndex++;
                    SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                }
                else if (key == '\r') { // ENTER
                    SoundEnter = engine->play2D("Enter.wav", false, false, true);
                    menuRunning = false;
                }
                system("cls");
            }

            if (selectedIndex == 1) {
                system("cls");
                cout << "\n\tStatistic of seance:\n";
                cout << "\tGames played: " << sessionGames << "\n";
                if (sessionGames > 0) {
                    cout << "\t- All time in game: " << totalPlayTime << " sec\n";
                    cout << "\t- Your record: " << moveArgs.recordSeconds << " sec\n";
                }
                else
                    cout << "\t- Have not data now.\n";
                system("pause");
                continue;
            }

            if (selectedIndex == 2) {
                system("cls");
                exit(1);
            }

            sessionGames++; // + запуск гри

            if (!SoundMenu->getIsPaused()) SoundMenu->setIsPaused(true);

            moveArgs.startTime = GetTickCount64(); // о час початку гри

            // Відлік + початковий рендер
            proxy.Move(&moveArgs);
            moveArgs.gameOver = false;
            SoundDriving = engine->play2D("Driving.wav", true, false, true);
            while (!moveArgs.gameOver) {
                if (_kbhit()) {
                    char ch = _getch();
                    switch (tolower(ch)) {
                    case 'w':
                        if (moveArgs.y > moveArgs.y1 + 1) {
                            moveArgs.y--;
                            SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                        }
                        break;
                    case 's':
                        if (moveArgs.y < moveArgs.y2 - 1) {
                            moveArgs.y++;
                            SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                        }
                        break;
                    case 'a':
                        if (moveArgs.x > moveArgs.x1 + 1) {
                            moveArgs.x--;
                            SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                        }
                        break;
                    case 'd':
                        if (moveArgs.x < moveArgs.x2 - 1) {
                            moveArgs.x++;
                            SoundPunctUp = engine->play2D("punct.wav", false, false, true);
                        }
                        break;
                    case 'q':
                        moveArgs.gameOver = true;
                        SoundEnter = engine->play2D("Enter.wav", false, false, true);
                        break;
                    }
                }

                proxy.Move(&moveArgs); // обробка логіки гри + рендер
                DWORD now = GetTickCount64();
                DWORD elapsedSec = (now - moveArgs.startTime) / 1000;

                real.goToxy(0, 32); // нижче за ігрове поле
                cout << "\tTime: " << elapsedSec - 3 << " sec   ";
                currentTime = elapsedSec-3;
                

                int baseDelay = 100;// базова затримка
                int levelEverySec = 3;// кожні 3 секунд — новий рівень
                int level = elapsedSec / levelEverySec;
                int delay = max(10, baseDelay - level * 10); // не менше 10 мс

                Sleep(delay); // динамічна затримка
                real.goToxy(0, 0);
            }
            SoundDriving->setIsPaused(true);
            SoundFeil = engine->play2D("feil.wav", false, false, true);
            Sleep(4000);
            system("cls");
            cout << "\n\tGame over!\n";
            cout << "\n\tCounting results...\n";
            SpeedResults.push_back(currentTime); //Додання останнього результату у список всіх
            totalPlayTime += currentTime; // Всього часу в гонках
            
            auto maxIt = std::max_element(SpeedResults.begin(), SpeedResults.end());
            if (maxIt != SpeedResults.end()) //Якщо д
                moveArgs.recordSeconds = *maxIt;
            SoundCountingScore = engine->play2D("tick.wav", false, false, true);
            Sleep(2000);
            system("cls");
            cout << "\n\tStatistic of this ride:\n";
                cout << "\t- Time: " << currentTime << " sec\n";
                cout << "\t- Your record: " << moveArgs.recordSeconds << " sec\n";
                cout << "\t- Obstacles wasted: " << moveArgs.wastedObstacles << "\n";
                if (currentTime == moveArgs.recordSeconds)
                    cout << "\n\t YOU DID RECORD\n";
            system("pause");

            SoundMenu->setIsPaused(false);

            moveArgs.wastedObstacles = 0; //Обнуляємо статистику
            moveArgs.firstGo = 0;
            moveArgs.x = (moveArgs.x2 + moveArgs.x1) / 2;
            moveArgs.y = (moveArgs.y2 + moveArgs.y1) / 2;
            real.obstacles.clear();
            real.setCounter(0);

            system("cls");
            continue;

            DWORD now = GetTickCount64();
            DWORD elapsedSec = (now - moveArgs.startTime) / 1000;
            totalPlayTime += elapsedSec - 3; 
        }

	}
    engine->drop(); // очистка
    return 0;
}
