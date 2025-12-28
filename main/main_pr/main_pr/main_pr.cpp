#include <iostream> 
#include <windows.h>
#include "Blackjack.h"
#include "Hangman.h"
#include "gonki.h"
#include "Tic_tac_toe.h"
using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int m = 0, score = 0;
    cout << "\t\t\t\t Добро пожаловать в сборник мини-игр!\n";
    cout << setw(119) << setfill('-') << "" << endl;
    cout << "\nДля перехода в главное меню нажмите Enter...";
    cin.get();
    system("cls");
    while (m != 5) {
        cout << setw(100) << setfill(' ') << "Очки: " << score << endl;
        cout << "Выберите игру из представленного списка:" << endl;
        cout << "\t\t\t\t Игры на очки\n";
        cout << "1 – Hangman - Виселица " << endl;
        cout << "2 – Blackjack " << endl;
        cout << "3 – Races (гонки)" << endl;
        cout << "\t\t\t\t Игры на двоих\n";
        cout << "4 – Tic-tac-toe - крестики-нолики " << endl;
        cout << "\t\t\t\t Выход\n";
        cout << "5 – Окончание программы, выход из меню выбора игр " << endl;

        if (!(cin >> m)) {
            cin.clear();  //сброс состояния потока (ошибка) 
            cin.ignore(10000, '\n'); //очистка буфера ввода 
            cout << "Ошибка: введён неверный символ. Введите число от 1 до 5." << endl; continue; //возвращаемся к началу цикла 
        }
        system("cls");
        switch (m)
        {
        case 1:

            score += Hangman();

            break;

        case 2:
            score += Blackjack();

            break;

        case 3:

            score += Races();

            break;

        case 4:
           Tic_tac_toe();

            break;

        case 5: cout << "Выход из программы... Спасибо за внимание!" << endl;
            break;

        default: cout << "Ошибка: такого пункта меню нет. Введите число от 1 до 5." << endl;
            break;
        }
    }
    return 0;
}
