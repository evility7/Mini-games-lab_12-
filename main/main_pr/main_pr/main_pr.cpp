#include <iostream> 
#include <windows.h>
using namespace std;

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int m = 0;

    while (m != 5) {

        cout << "Выберите игру из представленного списка:" << endl;

        cout << "1 – Hangman - Виселица " << endl;
        cout << "2 – Tic-tac-toe или проще говоря - крестики-нолики " << endl;
        cout << "3 – Races (гонки)" << endl; cout << "4 – Blackjack " << endl;
        cout << "5 – Окончание программы, выход из меню выбора игр " << endl;

        if (!(cin >> m)) {
            cin.clear();  //сброс состояния потока (ошибка) 
            cin.ignore(10000, '\n'); //очистка буфера ввода 
            cout << "Ошибка: введён неверный символ. Введите число от 1 до 5." << endl; continue; //возвращаемся к началу цикла 
        }

        switch (m)
        {
        case 1:

            Hangman();

            break;

        case 2:
            Tic_tac_toe();

            break;

        case 3:

            Races();

            break;

        case 4:

            Blackjack();

            break;

        case 5: cout << "Выход из программы... Спасибо за внимание!" << endl;
            break;

        default: cout << "Ошибка: такого пункта меню нет. Введите число от 1 до 5." << endl;
            break;
        }
    } return 0;
}
