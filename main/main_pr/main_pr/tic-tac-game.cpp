#include "Tic_tac_toe.h"
#include <iomanip>
using namespace std;

char board[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
char marker;
char player;
int count1 = 0;
int count2 = 0;

void drawBoard()
{
	system("cls"); //очищение поля при каждом вводе
	cout << setfill('-') << setw(119) << '\n';
	cout << "Игра крестики-нолики: \n";
	cout << setfill('-') << setw(120) << '\n' << '\n';
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << " " << board[i][j] << " ";
			if (j < 2)
			{
				cout << "|";
			}
		}
		if (i < 2)
		{
			cout << "\n---|---|---\n";
		}
	}
	cout << "\n\n";
}

//проверка не занята ли строка и куда вставлять символы
bool placeMarker(int slot)
{
	int row = (slot - 1) / 3; //в какую строку вставить
	int col = (slot - 1) % 3; //в какой столбец вставить

	if (board[row][col] != 'X' && board[row][col] != 'O')
	{
		board[row][col] = marker;
		return true;
	}
	return false;
}

//проверка выйгрыша
int winner()
{
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return player;
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return player;
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return player;
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return player;

	return 0;
}

//сброс поля
void resetBoard()
{
	char start = '1';
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = start++;
		}
	}
}

void game()
{
	resetBoard();
	char markerP1;
	while (true)
	{
		cout << "Игрок 1 , выберите маркер(X или O): ";
		cin >> markerP1;
		if (markerP1 == 'x') markerP1 = 'X';
		if (markerP1 == '0' || markerP1 == 'o') markerP1 = 'O';

		if (markerP1 == 'X' || markerP1 == 'O')
		{
			break;
		}
		else
		{
			cout << "Вы ввели неверный маркер. Повторите попытку: \n";
		}
	}
	player = 1;
	marker = markerP1;

	drawBoard();

	int player_won = 0;

	for (int i = 0; i < 9; i++)
	{
		int slot;
		cout << "Ход игрока " << player << " (" << marker << "). Введите номер клетки: ";
		cin >> slot;

		if (slot < 1 || slot > 9 || !placeMarker(slot) || cin.fail())
		{
			cout << "Ошибка! Клетка занята или введено неверное число. Попробуйте снова.\n";
			cin.clear();
			cin.ignore(1000, '\n');
			i--;
			continue;
		}

		drawBoard();
		player_won = winner();

		if (player_won != 0)
		{
			cout << "Поздравляю! Игрок " << player_won << " победил!";
			if (player == 1 && player == player_won)
			{
				count1++;
				cout << "\nОчки первого игрока: " << count1;
				cout << "\nОчки второго игрока: " << count2;
			}
			else
			{
				count2++;
				cout << "\nОчки первого игрока: " << count1;
				cout << "\nОчки второго игрока: " << count2;
			}
			break;
		}
		//смена игрока
		player = (player == 1) ? 2 : 1;
		marker = (marker == 'X') ? 'O' : 'X';
	}

	if (player_won == 0)
	{
		cout << "Ничья!";
		count1 = count1;
		count2 = count2;
		cout << "\nОчки первого игрока: " << count1;
		cout << "\nОчки второго игрока: " << count2;
	}
	cout << endl;
}

int Tic_tac_toe()
{
	setlocale(LC_ALL, "Russian");

	cout << "Вас приветствует игра Крестики-Нолики, ознакомьтесь с правилами игры: " << endl;
	cout << setfill('-') << setw(120) << '\n';
	cout << "Два игрока по очереди ставят свой знак (X или 0) в пустые клетки поля 3x3. \nЦель - первым собрать три своих символа в ряд. Победителю начисляется одно очко." << endl;
	cout << setfill('-') << setw(120) << '\n';
	cout << "\nДля начала игры нажмите Enter...";
	cin.get();
	cin.get();

	bool keepPlaying = true;

	while (keepPlaying)
	{
		system("cls");
		game();

		while (true)
		{
			cout << setfill('-') << setw(120) << '\n';
			cout << "Выберите действие:" << endl;
			cout << "1. Сыграть еще раз." << endl;
			cout << "2. Закончить игру." << endl;
			cout << setfill('-') << setw(120) << '\n';

			int again;
			cin >> again;
			//проверки на ввод
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}

			if (again == 1)
			{
				break;
			}
			else if (again == 2)
			{
				keepPlaying = false;
				break;
			}
			else
			{
				cout << "Ошибка! Введите цифру 1 или 2.\n";
			}
		}
	}

	cout << setfill('-') << setw(120) << '\n';
	cout << "ИТОГОВЫЙ СЧЕТ:" << endl;
	cout << "Очки первого игрока: " << count1 << endl;
	cout << "Очки второго игрока: " << count2 << endl;

	if (count1 > count2) cout << "Поздравляю! Игрок 1 победил в серии игр!" << endl;
	else if (count1 < count2) cout << "Поздравляю! Игрок 2 победил в серии игр!" << endl;
	else cout << "Ничья по итогам всех игр!" << endl;

	cout << "Конец игры! До свидания!" << endl;
	cout << setfill('-') << setw(120) << '\n';
	cout << "\nДля перехода в главное меню нажмите Enter...";
	cin.get();
	cin.get();
	system("cls");
	return 0;
}