#include <iostream>
#include <ctime>
#include <iomanip>
#include "main.h"

int putCard(); //набор карты
bool doCheck(int used_card[53], int card, int quantity); //проверка наличия карты в колоде
int countPoints(int point_card, int points); //подсчёт очков по набранным картам
int defineWinner(int user_points, int dealer_points, int main_points); //определение исхода игры 

using namespace std;

int blackjack()
{
    setlocale(LC_CTYPE, "Russian");
    srand((unsigned)time(NULL));
    bool condition = true;
    int action_counter = 0; //кол-во сыгранных игр
    int main_points = 0; //кол-во токенов, которые изменяются в зависимости от исхода игры
    //колода
    int deck[52][3]
    {
        //2
        {1, 2, 2}, {2, 2, 2}, {3, 2, 2}, {4, 2, 2},
        //3
        {1, 3, 3}, {2, 3, 3}, {3, 3, 3}, {4, 3, 3},
        //4
        {1, 4, 4}, {2, 4, 4}, {3, 4, 4}, {4, 4, 4},
        //5
        {1, 5, 5}, {2, 5, 5}, {3, 5, 5}, {4, 5, 5},
        //6
        {1, 6, 6}, {2, 6, 6}, {3, 6, 6}, {4, 6, 6},
        //7
        {1, 7, 7}, {2, 7, 7}, {3, 7, 7}, {4, 7, 7},
        //8
        {1, 8, 8}, {2, 8, 8}, {3, 8, 8}, {4, 8, 8},
        //9
        {1, 9, 9}, {2, 9, 9}, {3, 9, 9}, {4, 9, 9},
        //10
        {1, 10, 10}, {2, 10, 10}, {3, 10, 10}, {4, 10, 10},
        //валет
        {1, 11, 10}, {2, 11, 10}, {3, 11, 10}, {4, 11, 10},
        //дама
        {1, 12, 10}, {2, 12, 10}, {3, 12, 10}, {4, 12, 10},
        //король
        {1, 13, 10}, {2, 13, 10}, {3, 13, 10}, {4, 13, 10},
        //туз
        {1, 14, 11}, {2, 14, 11}, {3, 14, 11}, {4, 14, 11},
    };
    while (condition) 
    {
        bool cin_fail1 = false, cin_fail2 = false;
        int action = 0, y = 0, card = 0, quantity = 0, user_points = 0, point_card = 0, dealer_card = 0, dealer = 0, user = 0, dealer_points = 0;
        int used_cards[52]{}; //использованные карты
        int user_cards[52]{}; //карты пользователя
        int dealer_cards[52]{}; //карты дилера
        //интерфейс
        cout << "\t\t\t\t Рады приветсвовать вас за игровым столом Blackjack! \n";
        cout << setw(119) << setfill('-') << "" << endl;
        if (action_counter == 0)
        {
            cout << "Правила игры:\n";
            cout << " => Цель игры — собрать карты с суммой очков как можно ближе к 21, но не больше.\n";
            cout << " => Туз может быть 1 или 11, картинки (валет, дама, король) — это 10, остальные карты считаются по числу.\n";
            cout << " => Ты играешь только против дилера: если у тебя перебор (свыше 21), ты сразу проигрываешь.\n";
            cout << " => Победа — когда твоя сумма ближе к 21, чем у дилера, и при этом не выше 21.\n";
            cout << " => За Blackjack начисляется 2 токена, за победу - 1, а при поражении 1 токен списывается, если их кол-во не равно 0\n";
            cout << setw(119) << setfill('-') << "" << endl;
            cout << "С болеее подробными правилами можете ознакомиться на интернет-ресурсе:\nhttps://www.shambalacasino.ru/blog/pravila-igri-v-blekdjek \n";
            cout << setw(119) << setfill('-') << "" << endl;
            cout << "Нажмите Enter для начала игры";
            cin.get();
            for (int i = 0; i < 11; i++)
                cout << "\033[A\33[2K";
        }
        else
        {
            cout << "Нажмите Enter для начала игры";
            cin.get();
            cout << "\033[A\33[2K";
        }
        //начальная раздача карт дилеру и игроку
        for (int i = 0; i < 2; i++)
        {
            //набор карты и проерка на использование
            do
            {
                dealer_card = putCard();
            } while (doCheck(used_cards, dealer_card, quantity) == false);
            //занесение карт в массивы, которые в дальнейшем используются для проверки и вывода карт
            used_cards[quantity] = dealer_card;
            dealer_cards[dealer] = dealer_card;
            quantity++;
            dealer++;
            point_card = deck[dealer_card][2];
            dealer_points = countPoints(point_card, dealer_points);
            //набор карты и проерка на использование
            do
            {
                card = putCard();
            } while (doCheck(used_cards, card, quantity) == false);
            //занесение карт в массивы, которые в дальнейшем используются для проверки и вывода карт
            used_cards[quantity] = card;
            user_cards[user] = card;
            quantity++;
            user++;
            point_card = deck[card][2];
            user_points = countPoints(point_card, user_points);
        }
        //вывод карты
        cout << "Карты диллера: " << setw(100) << setfill(' ') << "Токены: " << main_points << endl;
        for (int i = 0; i <= dealer - 1; i++)
            if (i == 0) outputCard(deck, dealer_cards[i]);
            else cout << " *";
        cout << endl;
        cout << "Ваши карты: \n";
        for (int i = 0; i <= user - 1; i++)
            outputCard(deck, user_cards[i]);
        cout << endl;
        cout << "Ваши очки: " << user_points << endl;
        cout << setw(119) << setfill('-') << "" << endl;
        cout << "Выберите действия: \n";
        cout << "1 - взять карту\n";
        cout << "2 - остановить набор\n";
        cout << setw(119) << setfill('-') << "" << endl;
        do
        {
            cin >> action; // выбор действия
            if (cin_fail1 == true)
            {
                for (int i = 0; i < 2; i++)
                    cout << "\033[A\33[2K";
            }
            //исправление ошибки ввода при наличии
            if (cin.fail()) 
            { 
                cout << "\033[A\33[2K";
                cin_fail1 = true;
                cout << "Ошибка ввода! Попробуйте еще раз." << endl;
                cin.clear(); 
                cin.ignore(10000, '\n'); 
            }
            else
            {
                cin_fail1 = false;
                cout << "\033[A\33[2K";
            }
            switch (action)
            {
            case 1:
            {
                //набор карты игроком
                //набор карты и проерка на использование
                do
                {
                    card = putCard();
                } while (doCheck(used_cards, card, quantity) == false);
                //занесение карт в массивы, которые в дальнейшем используются для проверки и вывода карт
                used_cards[quantity] = card;
                user_cards[user] = card;
                quantity++;
                user++;
                //вывод карт и очков игрока
                if (user > 3)
                {
                    for (int i = 0; i < 3; i++)
                        cout << "\033[A\33[2K";
                }
                cout << "Ваши карты: \n";
                for (int i = 0; i <= user - 1; i++)
                    outputCard(deck, user_cards[i]);
                cout << endl;
                point_card = deck[card][2];
                user_points = countPoints(point_card, user_points);
                cout << "Ваши очки: " << user_points << endl;
                //проверка на 21
                if (user_points > 21)
                {
                    y = 1;
                    if (main_points > 0)
                    {
                        main_points--;
                        cout << "Вы проиграли. У вас списан 1 токен.\n";
                    }
                    else cout << "Вы проиграли.\n";
                }
                break;
            }
            case 2:
            {
                y = 1;
                //донабор карт дилером, если очков < 17
                if (dealer_points < 17)
                {
                    //набор карты и проерка на использование
                    do
                    {
                        dealer_card = putCard();
                    } while (doCheck(used_cards, dealer_card, quantity) == false);
                    //занесение карт в массивы, которые в дальнейшем используются для проверки и вывода карт
                    used_cards[quantity] = dealer_card;
                    dealer_cards[dealer] = dealer_card;
                    quantity++;
                    dealer++;
                    point_card = deck[dealer_card][2];
                    dealer_points = countPoints(point_card, dealer_points);
                }
                //вывод карт и очков дилера
                if (user >= 3)
                {
                    for (int i = 0; i < 3; i++)
                        cout << "\033[A\33[2K";
                }
                cout << "Ваши карты: \n";
                for (int i = 0; i <= user - 1; i++)
                    outputCard(deck, user_cards[i]);
                cout << endl;
                cout << "Карты дилера: \n";
                for (int i = 0; i <= dealer - 1; i++)
                    outputCard(deck, dealer_cards[i]);
                cout << "\nВаши очки: " << user_points;
                cout << "\nОчки дилера: " << dealer_points << endl;
                main_points = defineWinner(user_points, dealer_points, main_points);
                break;
            }
            default:
            {
                cout << "Выберите действие из списка\n";
                break;
            }
            }
        } while (y == 0);
        cout << setw(119) << setfill('-') << "" << endl;
        int c = 0;
        bool g = false;
        //вывод интерфейса для продолжения/завершения игры
        cout << "Для новой игры нажмите 1, для выхода - 2\n";
        cin >> c;
        //проверка правильно введённого выбора, предложенного в интерфейсе
        if (c != 1 && c != 2)
        {
            while (g == false)
            {
                if (cin_fail2 == true)
                        cout << "\033[A\33[2K";
                //исправление ошибки ввода при наличии
                if (cin.fail())
                {
                    cout << "\033[A\33[2K";
                    cin_fail2 = true;
                    cout << "Ошибка ввода! Попробуйте еще раз.";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else
                {
                    cin_fail2 = false;
                    cout << "\033[A\33[2K";
                }
                cout << "\nНеверная команда, попробуйте ещё раз: ";
                cin >> c;
                if (c == 1 || c == 2) g = true;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //очистка буфера для корректного повторного запуска игры
        //продолжить/закончить игру
        switch (c)
        {
        case 1:
        {
            system("cls");
            break;
        }
        case 2:
        {
            condition = false;
            break;
        }
        }
        action_counter++;
    }
    //окончание игры и вывод кол-во полученных токенов
    system("cls");
    cout << "Вы завершили игровую сессию\n";
    cout << "Полученные токены: " << main_points << endl;
    return 0;
}

int putCard()
{
    int card = 0;
    card = rand() % 52;
    return card;
}

bool doCheck(int used_card[53], int card, int quantity)
{
    for (int i = 0; i < quantity; i++) 
        if (used_card[i] == card)
            return false;
    return true;
}

int countPoints(int point_card, int points)
{
    if (point_card == 11)
    {
        if (points + 11 <= 21) points += 11;
        else points += 1;
    }
    else
    {
        points += point_card;
    }
    return points;
}

int defineWinner(int user_points, int dealer_points, int main_points)
{
    if (user_points == dealer_points) cout << "Ничья\n";
    else
        if (user_points == 21 && dealer_points != 21)
        {
            cout << "Blackjack! Вам начисленно 2 токена!\n";
            main_points += 2;
        }
        else
            if (user_points > dealer_points && user_points < 21)
            {
                cout << "Поздравляем, вы победили! Вам начислен 1 токен!\n";
                main_points++;
            }
            else 
                if (user_points < dealer_points && dealer_points <= 21)
                {
                    if (main_points > 0)
                    {
                        main_points--;
                        cout << "Вы проиграли. У вас списан 1 токен.\n";
                    }
                    else cout << "Вы проиграли.\n";
                }
                else
                    if (user_points < 21 && dealer_points > 21)
                    {
                        cout << "Поздравляем, вы победили! Вам начислен 1 токен!\n";
                        main_points++;
                    }
    return main_points;
}
