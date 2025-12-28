#include <iostream>
#include <windows.h>
#include <iomanip>
#include "Blackjack.h"
#include "Hangman.h"
#include "gonki.h"
#include "Tic_tac_toe.h"

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int m = 0, score = 0;

    // Приветствие
    setColor(11); // голубой
    cout << "\n===============================================================\n";
    cout << "\t\t Добро пожаловать в сборник мини-игр!\n";
    cout << "===============================================================\n\n";
    setColor(7); // стандартный серый
    cout << "Для перехода в главное меню нажмите Enter...";
    cin.get();
    system("cls");

    while (m != 5) {
        setColor(14); // жёлтый
        cout << setw(100) << setfill(' ') << "Очки: " << score << endl;
        cout << "---------------------------------------------------------------\n";
        setColor(10); // зелёный
        cout << "Выберите игру из представленного списка:\n\n";

        setColor(11); // голубой
        cout << "\t\t Игры на очки\n";
        setColor(7);
        cout << "1 – Hangman (Виселица)\n";
        cout << "2 – Blackjack\n";
        cout << "3 – Races (Гонки)\n\n";

        setColor(13); // розовый
        cout << "\t\t Игры на двоих\n";
        setColor(7);
        cout << "4 – Tic-tac-toe (Крестики-нолики)\n\n";

        setColor(12); // красный
        cout << "\t\t Выход\n";
        setColor(7);
        cout << "5 – Завершение программы\n";
        setColor(14);
        cout << "---------------------------------------------------------------\n";
        setColor(7);
        // Проверка ввода
        if (!(cin >> m)) {
            cin.clear();
            cin.ignore(10000, '\n');
            setColor(12);
            cout << "Ошибка: введён неверный символ. Введите число от 1 до 5.\n";
            setColor(7);
            continue;
        }
        system("cls");

        // Обработка выбора
        switch (m) {
        case 1: score += Hangman(); break;
        case 2: score += Blackjack(); break;
        case 3: score += Races(); break;
        case 4: Tic_tac_toe(); break;
        case 5:
            setColor(11);
            cout << "Выход из программы... Спасибо за внимание!\n";
            setColor(7);
            break;
        default:
            setColor(12);
            cout << "Ошибка: такого пункта меню нет. Введите число от 1 до 5.\n";
            setColor(7);
            break;
        }
    }
    return 0;
}

