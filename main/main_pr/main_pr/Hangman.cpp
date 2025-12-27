#include "Hangman.h"

using namespace std;

const int MAX_WORDS = 32;
const int MAX_USED = 32;

// Технологии
string tech[MAX_WORDS] = {
    "КОМПЬЮТЕР","НОУТБУК","МОНИТОР","КЛАВИАТУРА","МЫШЬ","ПРОЦЕССОР","ИНТЕРНЕТ",
    "СЕРВЕР","ПРОГРАММА","КОД","АЛГОРИТМ","БАЗА","СЕТЬ","ОБЛАКО","РОБОТ","ДРОН",
    "ГАДЖЕТ","ПРИЛОЖЕНИЕ","СМАРТФОН","ПЛАНШЕТ","ФАЙЛ","ПАПКА","КЛАВИША","ПАРОЛЬ",
    "ПОЧТА","БРАУЗЕР","ВИДЕОКАРТА","ПАМЯТЬ","КОНТРОЛЛЕР","ДРАЙВЕР","СИСТЕМА"
};
int tech_count = 31;

// Животные
string animals[MAX_WORDS] = {
    "КОШКА","СОБАКА","ЛЕВ","ТИГР","СЛОН","ЖИРАФ","КРОКОДИЛ","ОБЕЗЬЯНА","РЫБА",
    "ДЕЛЬФИН","АКУЛА","МЕДВЕДЬ","ЛИСА","ВОРОБЕЙ","ОРЁЛ","ВОРОНА","ПАУК","ЧЕРЕПАХА",
    "КЕНГУРУ","КРОЛИК","ВОЛК","ТИГРЁНОК","ЯГНЁНОК","МУРАВЕЙ","КОАЛА","КАБАН","СУРИКАТ",
    "ПИНГВИН","ФЕНИКС","ГРИФОН","МОРЖ"
};
int animals_count = 32;

// Еда
string food[MAX_WORDS] = {
    "КВАС","СУП","БОРЩ","ПЕЛЬМЕНИ","ХЛЕБ","СЫР","КОЛБАСА","МОЛОКО","ЧАЙ","КОФЕ",
    "МОРОЖЕНОЕ","ШОКОЛАД","ЯБЛОКО","АПЕЛЬСИН","БАНАН","ВИНОГРАД","ОГУРЕЦ","ПОМИДОР",
    "КАРТОФЕЛЬ","РИС","КУРИЦА","ИНДЕЙКА","САЛАТ","ПИЦЦА","БУРГЕР","ТОРТ","МАСЛО",
    "МЕД","ЛИМОН","ГРУША","КАПУСТА"
};
int food_count = 31;

// Города
string cities[MAX_WORDS] = {
    "МОСКВА","НОВОСИБИРСК","СЕУЛ","ТОКИО","ПАРИЖ","ЛОНДОН","РИМ","БЕРЛИН","ПЕКИН",
    "ДЕЛИ","МЕЛЬБУРН","СИДНЕЙ","ВЕНА","АМСТЕРДАМ","КАИР","НЬЮЙОРК","САНФРАНЦИСКО",
    "БУЭНОСАЙРЕС","ТОРОНТО","ПРАГА","СТОКГОЛЬМ","ОСЛО","ХАНОЙ","БАНГКОК","СИНГАПУР"
};
int cities_count = 25;

// Природа
string nature[MAX_WORDS] = {
    "ДОЖДЬ","СНЕГ","ВЕТЕР","ОБЛАКО","СОЛНЦЕ","ЛУНА","ЗВЕЗДА","ТУМАН","РАДУГА",
    "ГОРА","РЕКА","ОЗЕРО","МОРЕ","ОКЕАН","ЛЕС","ПУСТЫНЯ","ВУЛКАН","ЛАВИНА","ГРОЗА",
    "БУРЯ","ДЮНА","ВОДОПАД","СТЕПЬ","БОЛОТО","КАМЕНЬ","ПЕЩЕРА","ЛАВА","САД"
};
int nature_count = 29;

// Профессии
string jobs[MAX_WORDS] = {
    "ЧЕЛОВЕК","ВРАЧ","УЧИТЕЛЬ","ПРОГРАММИСТ","ИНЖЕНЕР","ДИЗАЙНЕР","ПЕВЕЦ","АКТЁР",
    "ХУДОЖНИК","ВОДИТЕЛЬ","ПОВАР","СПОРТСМЕН","ПОЛИЦЕЙСКИЙ","УЧЁНЫЙ","ФЕРМЕР","ПИСАТЕЛЬ",
    "ЖУРНАЛИСТ","АДВОКАТ","ДИРЕКТОР","СТУДЕНТ","ДРУГ","СОЛДАТ","МУЗЫКАНТ","АРХИТЕКТОР",
    "САДОВОД","ПАРИКМАХЕР","ФЛОРИСТ"
};
int jobs_count = 27;

// Разное
string misc[MAX_WORDS] = {
    "КНИГА","РУЧКА","КАРАНДАШ","СТУЛ","СТОЛ","ЛАМПА","ТЕЛЕФОН","ОЧКИ","ОДЕЖДА",
    "ОБУВЬ","СУМКА","ЧАСЫ","ДВЕРЬ","ОКНО","КРОВАТЬ","МАШИНА","АВТОБУС","ПОЕЗД",
    "БИЛЕТ","КЛЮЧ","МУЗЫКА","ФИЛЬМ","ИГРА","ПРАЗДНИК","ПЛАНЕТА","КОРАБЛЬ","СТАРТАП",
    "ФОНАРЬ","КАРТА","СПОРТ","ОСТРОВ"
};
int misc_count = 31;

// ASCII арт (CP1251-совместимый)
string display_hangman(int tries) {
    string stages[7] = {
        " +---+\n |   O\n |  /|\\\n |  / \\\n +---\n",
        " +---+\n |   O\n |  /|\\\n |  /  \n +---\n",
        " +---+\n |   O\n |  /|\\\n |     \n +---\n",
        " +---+\n |   O\n |  /|\n |     \n +---\n",
        " +---+\n |   O\n |   |\n |     \n +---\n",
        " +---+\n |   O\n |     \n |     \n +---\n",
        " +---+\n |     \n |     \n |     \n +---\n"
    };
    return stages[tries];
}

// Проверка на русские буквы в CP1251
bool isRussianCP1251(const string& s) {
    if (s.empty()) return false;
    for (unsigned char uc : s) { // перебор символов
        // Разрешаем А..Я, а..я, Ё (0xA8), ё (0xB8) в CP1251
        bool upperLower = (uc >= 0xC0 && uc <= 0xFF); // кириллица
        bool yo = (uc == 0xA8 || uc == 0xB8);         // Ё/ё
        if (!(upperLower || yo)) return false;
    }
    return true;
}

string get_category() {
    while (true) {
        cout << "Выберите категорию:\n";
        cout << "1. Технологии\n2. Животные\n3. Еда\n4. Города\n5. Природа\n6. Профессии\n7. Разное\n";
        string choice;
        cin >> choice;
        if (choice == "1") return "Технологии";
        if (choice == "2") return "Животные";
        if (choice == "3") return "Еда";
        if (choice == "4") return "Города";
        if (choice == "5") return "Природа";
        if (choice == "6") return "Профессии";
        if (choice == "7") return "Разное";
        cout << "Введите число от 1 до 7\n";
    }
}

string get_word(const string& category) {
    if (category == "Технологии") return tech[rand() % tech_count];
    if (category == "Животные")   return animals[rand() % animals_count];
    if (category == "Еда")        return food[rand() % food_count];
    if (category == "Города")     return cities[rand() % cities_count];
    if (category == "Природа")    return nature[rand() % nature_count];
    if (category == "Профессии")  return jobs[rand() % jobs_count];
    if (category == "Разное")     return misc[rand() % misc_count];
}

// Преобразование строки к верхнему регистру
void to_upper_local(string& s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = toupper((unsigned char)s[i]);
    }
}

bool in_array(const string arr[], int count, const string& val) { // проверка на уже введенные
    for (int i = 0; i < count; ++i) {
        if (arr[i] == val) return true;
    }
    return false;
}

void print_used(const string letters[], int lcount, const string words[], int wcount) { // вывод уже введенных букв и слов
    cout << "Использованные буквы: ";
    if (lcount == 0) cout << "-";
    for (int i = 0; i < lcount; ++i) {
        cout << letters[i] << (i + 1 < lcount ? ", " : "");
    }
    cout << "\nИспользованные слова: ";
    if (wcount == 0) cout << "-";
    for (int i = 0; i < wcount; ++i) {
        cout << words[i] << (i + 1 < wcount ? ", " : "");
    }
    cout << "\n";
}

void Hangman() {
    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "Привет, давай сыграем в виселицу!\n\n";
    cout << "Правила: " << endl;
    cout << "- Угадай слово по буквам или целиком за 6 попыток\n\n";
    cout << "Нажмите Enter для начала:" << endl;
    cin.get();
    system("cls");
    int score = 0;

    while (true) {
        int tries = 6;
        int hints = 2;

        // хранилища использованных букв и слов
        string used_letters[MAX_USED];
        int used_letters_count = 0;
        string used_words[MAX_USED];
        int used_words_count = 0;

        string category = get_category();
        string word = get_word(category);
        string completion(word.size(), '_');

        cout << "Слово загадано: " << completion << "\n";

        while (tries > 0 && completion.find('_') != string::npos) {

            cout << "Осталось попыток: " << tries << "\n";
            print_used(used_letters, used_letters_count, used_words, used_words_count);

            cout << "Введите букву или слово (только русские символы): ";
            string guess;
            cin >> guess;

            // проверка на кириллицу (CP1251)
            if (!isRussianCP1251(guess)) {
                cout << "Ошибка: допускаются только русские буквы.\n";
                continue;
            }

            to_upper_local(guess);

            if (guess.size() == 1) {
                // проверка на повтор буквы
                if (in_array(used_letters, used_letters_count, guess)) {
                    cout << "Эта буква уже была. Введите новую.\n";
                    continue;
                }
                // добавить в список использованных букв
                if (used_letters_count < MAX_USED) used_letters[used_letters_count++] = guess;

                bool ok = false;
                for (size_t i = 0; i < word.size(); ++i) {
                    if (word[i] == guess[0]) {
                        completion[i] = word[i];
                        ok = true;
                    }
                }
                if (ok) {
                    cout << "Есть такая буква! " << completion << "\n";
                }
                else {
                    cout << "Нет такой буквы. " << completion << "\n";
                    --tries;
                    cout << display_hangman(tries);
                }
            }
            else {
                // проверка на повтор слова
                if (in_array(used_words, used_words_count, guess)) {
                    cout << "Это слово уже было. Введите новое.\n";
                    continue;
                }
                if (used_words_count < MAX_USED) used_words[used_words_count++] = guess;

                if (guess == word) {
                    completion = word;
                    break;
                }
                else {
                    cout << "Слово неверно. " << completion << "\n";
                    --tries;
                    cout << display_hangman(tries);
                }
            }

            // подсказка при малом числе попыток
            if (tries <= 2 && hints > 0 && completion.find('_') != string::npos) {
                string ans;
                while (true) {
                    cout << "Хотите подсказку? (0 - да / 1 - нет): ";
                    cin >> ans;

                    if (ans == "0") {
                        for (size_t i = 0; i < word.size(); ++i) {
                            if (completion[i] == '_') {
                                completion[i] = word[i];
                                --hints;
                                cout << "Подсказка: " << completion << "\n";
                                break;
                            }
                        }
                        break; // выходим из цикла проверки после использования подсказки
                    }
                    else if (ans == "1") {
                        // пользователь отказался от подсказки
                        break;
                    }
                    else {
                        cout << "Ошибка ввода. Введите 0 (да) или 1 (нет).\n";
                    }
                }
            }
            cout << "--------------------------------------------------\n";
        }

        cout << "--------------------------------------------------\n";
        if (completion == word) {
            score += 5;
            cout << "Поздравляю, вы победили! Загаданное слово: " << word << "\n";
            cout << "Общее количество очков: " << score << "\n";
        }
        else {
            cout << "К сожалению, вы проиграли.\n";
            cout << "Загаданное слово было: " << word << "\n";
            cout << "Общее количество очков: " << score << "\n";
        }

        while (true) {
            cout << "Сыграть ещё раз? (0 - да / 1 - нет): ";
            string again;
            cin >> again;

            // проверка на допустимый ввод
            if (again == "0") {
                system("cls");
                break; // выходим из цикла проверки и продолжаем игру
            }
            else if (again == "1") {
                system("cls");
                cout << "Общее количество очков: " << score << "\n";
                cout << "До новых встреч! \n";
                return; // завершаем функцию play()
            }
            else {
                cout << "Ошибка ввода. Введите 0 (да) или 1 (нет).\n";
                continue; // повторить запрос
            }
        }
    }
    system("cls");
}