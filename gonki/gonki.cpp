#include <iostream>
#include <ctime>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	const int H = 15;
	const int L = 20;
	int driver = L/2;
	int difficulty[H];
	int score = 0;


	for (int i = 0; i < H; i++) {
		difficulty[i] = -1;
	}
	srand(time(0));
	while (true) {

		//ТРАССА

		system("cls");
		for (int i = 0; i < H; i++) {
			cout << "|";
			for (int j = 0; j < L; j++) {
				if (i == H - 1 && j == driver)
					cout << "H";
				else
					if (difficulty[i] == j)
					cout << "#";
				else
					cout << " ";
			}
			cout << "|"<<endl;
		}

		// УПРАВЛЕНИЕ

		if (_kbhit()) {
			char control = _getch();
			if (control == 'a' || control == 'A') {
				if (driver > 0) {
					driver--;
				}
			}
			if (control == 'd' || control == 'D') {
				if (driver < L - 1) {
					driver++;
				}
			}
		}

		//ЛОГИКА

		for (int j = H - 1; j > 0; j--) {
			difficulty[j] = difficulty[j - 1];
		}
		if (rand() % 4 == 0)
			difficulty[0] = rand() % L;
		else
			difficulty[0] = -1;
		if (difficulty[H-1] == driver) {
			system("cls");
			cout << "Ты врезался! Игра окончена:(" << endl;
			cout << "Твой счёт: " << score << "\n";
			return 0;
		}
		score++;
		Sleep(30);
	}
}
