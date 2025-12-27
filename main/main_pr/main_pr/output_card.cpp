#include <iostream>
#include <locale>
#include <io.h>
#include <fcntl.h>
#include "output_card.h"
using namespace std;
void outputCard(int deck[52][3], int i)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    switch (deck[i][0])
    {
    case 1: wcout << L"\u2665 "; break;
    case 2: wcout << L"\u2666 "; break;
    case 3: wcout << L"\u2663 "; break;
    case 4: wcout << L"\u2660 "; break;
    }
    _setmode(_fileno(stdout), _O_TEXT);
    setlocale(LC_ALL, "Russian");
    switch (deck[i][1])
    {
    case 2: cout << "двойка "; break;
    case 3: cout << "тройка "; break;
    case 4: cout << "четвёрка "; break;
    case 5: cout << "пятёрка "; break;
    case 6: cout << "шестёрка "; break;
    case 7: cout << "семёрка "; break;
    case 8: cout << "восьмёрка "; break;
    case 9: cout << "девятка "; break;
    case 10: cout << "десятка "; break;
    case 11: cout << "валет "; break;
    case 12: cout << "дама "; break;
    case 13: cout << "король "; break;
    case 14: cout << "туз "; break;
    }
}