#include "MoveArgs.h"
#include "RealImage.h"
#include "ProxyRealImage.h"
#include<Windows.h> 
#include<conio.h> // для зчитування клавіш
#include <iostream>
#include <cstdlib> // для очистки екрануф

using namespace std;

int main() {

	MoveArgs moveArgs;
	int a, b;

	//Користувацькі налаштування
	cout << "\n\tHello! Here you can recive color of pixel your image";
	cout << "\n\tEnter size of your image (\"HEIGHT WIDTH\") though space: ";
	cin >> a >> b;
	system("cls");


	moveArgs.x1 = 0;
	moveArgs.x2 = b;
	moveArgs.y1 = 0;
	moveArgs.y2 = a;
	moveArgs.x = (moveArgs.x2 - moveArgs.x1) / 2;
	moveArgs.y = (moveArgs.y2 - moveArgs.y1) / 2;
	RealImage A;
	ProxyRealImage B;
	B.SetObjectRealImage(&A);
	bool ImageProccess = true;
	B.Move(&moveArgs);
	char ch = 'W';
	while (ImageProccess)
	{
		if (_kbhit()) { // Перевіряємо, чи була натиснута клавіша
			ch = _getch(); // Зчитуємо символ без виведення на екран

			if (ch == 'w' || ch == 'W') {
				moveArgs.y--;
				B.Move(&moveArgs);
			}
			else if (ch == 'a' || ch == 'A') {
				moveArgs.x--;
				B.Move(&moveArgs);
			}
			else if (ch == 's' || ch == 'S') {
				moveArgs.y++;
				B.Move(&moveArgs);
			}
			else if (ch == 'd' || ch == 'D') {
				moveArgs.x++;
				B.Move(&moveArgs);
			}
			else if (ch == 'q' || ch == 'Q') {
				break; // Вихід
			}
			
		}
		Sleep(50);
	}

	return 0;
}